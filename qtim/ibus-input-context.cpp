/* vim:set et ts=4 sts=4 : */
/*
 * ibus - The Input Bus
 *
 * Copyright (c) 2007-2008 Huang Peng <shawn.p.huang@gmail.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this program; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place, Suite 330,
 * Boston, MA  02111-1307  USA
 */
#include <QtDebug>
#include <QInputMethodEvent>
#include <QTextCharFormat>
#include <qibus.h>
#include "ibus-input-context.h"

#ifdef Q_WS_X11
# include <QX11Info>
# include <X11/Xlib.h>
# include <X11/keysym.h>
# include <X11/Xutil.h>
# ifdef HAVE_X11_XKBLIB_H
#  define HAVE_XKB
#  include <X11/XKBlib.h>
# endif
#endif

#include <stdlib.h>

#include <ibuskeysyms.h>
#include "ibus-compose-data.h"

typedef struct _IBusComposeTableCompact IBusComposeTableCompact;
struct _IBusComposeTableCompact {
    const quint16 *data;
    int max_seq_len;
    int n_index_size;
    int n_index_stride;
};

static const IBusComposeTableCompact ibus_compose_table_compact = {
    ibus_compose_seqs_compact,
    5,
    23,
    6
};

static const uint ibus_compose_ignore[] = {
    IBUS_Shift_L,
    IBUS_Shift_R,
    IBUS_Control_L,
    IBUS_Control_R,
    IBUS_Caps_Lock,
    IBUS_Shift_Lock,
    IBUS_Meta_L,
    IBUS_Meta_R,
    IBUS_Alt_L,
    IBUS_Alt_R,
    IBUS_Super_L,
    IBUS_Super_R,
    IBUS_Hyper_L,
    IBUS_Hyper_R,
    IBUS_Mode_switch,
    IBUS_ISO_Level3_Shift,
    IBUS_VoidSymbol
};

typedef QInputMethodEvent::Attribute QAttribute;

IBusInputContext::IBusInputContext (const BusPointer &bus)
    : m_bus (bus),
      m_context (NULL),
      m_preedit (NULL),
      m_preedit_visible (false),
      m_preedit_cursor_pos (0),
      m_has_focus (false),
      m_caps (CapPreeditText | CapFocus),
      m_n_compose (0)
{
    Q_ASSERT (!m_bus.isNull ());

    m_compose_buffer[0] =
    m_compose_buffer[1] =
    m_compose_buffer[2] =
    m_compose_buffer[3] =
    m_compose_buffer[4] =
    m_compose_buffer[5] =
    m_compose_buffer[6] =
    m_compose_buffer[7] = 0;

    createInputContext ();

    connect (m_bus, SIGNAL (connected (void)),
             this, SLOT (slotConnected (void)));
    connect (m_bus, SIGNAL (disconnected (void)),
             this, SLOT (slotDisconnected (void)));

}

IBusInputContext::~IBusInputContext (void)
{
    // client->releaseInputContext (this);
    deleteInputContext ();
    m_preedit = NULL;
    m_context = NULL;
    m_bus = NULL;
}


bool
IBusInputContext::filterEvent (const QEvent *event)
{
    return QInputContext::filterEvent (event);
}

QFont
IBusInputContext::font (void) const
{
    return QInputContext::font ();
}

QString
IBusInputContext::identifierName (void)
{
    return QString ("ibus");
}

QString
IBusInputContext::language (void)
{
    return QString ("");
}

void
IBusInputContext::mouseHandler (int x, QMouseEvent *event)
{
    QInputContext::mouseHandler (x, event);
}

void
IBusInputContext::reset (void)
{
}

void
IBusInputContext::update (void)
{
    QWidget *widget = focusWidget ();

    if (widget == NULL || m_context.isNull ()) {
        return;
    }

    QRect rect = widget->inputMethodQuery(Qt::ImMicroFocus).toRect ();

    QPoint topleft = widget->mapToGlobal(QPoint(0,0));
    rect.translate (topleft);

    m_context->setCursorLocation (rect.x (), rect.y (), rect.width (), rect.height ());

#if 0
    QVariant value;
    qDebug () << "== update == ";
    value = widget->inputMethodQuery(Qt::ImMicroFocus);
    qDebug () << "Qt::ImMicroFocus " << value;
    value = widget->inputMethodQuery(Qt::ImFont);
    qDebug () << "Qt::ImFont " <<value;
    value = widget->inputMethodQuery(Qt::ImCursorPosition);
    qDebug () << "Qt::ImCursorPosition " << value;
    value = widget->inputMethodQuery(Qt::ImSurroundingText);
    qDebug () << "Qt::ImSurroundingText " << value;
    value = widget->inputMethodQuery(Qt::ImCurrentSelection);
    qDebug () << "Qt::ImCurrentSelection " << value;
#endif
}

bool
IBusInputContext::isComposing (void) const
{
    return m_preedit_visible && !m_preedit;
}

void
IBusInputContext::setFocusWidget (QWidget *widget)
{
    QInputContext::setFocusWidget (widget);

    m_has_focus = (widget != NULL);

    if (m_context.isNull ())
        return;

    if (m_has_focus) {
        m_context->focusIn ();
    }
    else {
        m_context->focusOut ();
    }
    update ();
}

void
IBusInputContext::widgetDestroyed (QWidget *widget)
{
    QInputContext::widgetDestroyed (widget);

    if (m_has_focus) {
        setFocusWidget (NULL);
    }

    update ();
}

#ifdef Q_WS_X11

static inline bool
translate_x_key_event (XEvent *xevent, uint *keyval, uint *keycode, uint *state)
{
    Q_ASSERT (xevent);
    Q_ASSERT (keyval);
    Q_ASSERT (keycode);
    Q_ASSERT (state);

    if (xevent->type != KeyPress && xevent->type != KeyRelease)
        return false;

    *keycode = xevent->xkey.keycode;
    *state = xevent->xkey.state;
    if (xevent->type == KeyRelease)
        *state |= IBus::ReleaseMask;

    char key_str[64];
    if (XLookupString (&xevent->xkey, key_str, sizeof (key_str), (KeySym *)keyval, 0) <= 0) {
        *keyval = (quint32) XLookupKeysym (&xevent->xkey, 0);
    }

    return true;

}

bool
IBusInputContext::x11FilterEvent (QWidget *keywidget, XEvent *xevent)
{
    uint keyval = 0;
    uint keycode = 0;
    uint state = 0;

    translate_x_key_event (xevent, &keyval, &keycode, &state);
    keycode -= 8;

    if (!m_context.isNull ()) {
        if (m_context->processKeyEvent (keyval, keycode, state)) {
            return true;
        }
    }

    return processCompose (keyval, state);

    return QInputContext::x11FilterEvent (keywidget, xevent);
}

bool
IBusInputContext::processCompose (uint keyval, uint state)
{
    int i;

    if (state & IBus::ReleaseMask)
        return false;

    for (i = 0; ibus_compose_ignore[i] != IBUS_VoidSymbol; i++) {
        if (keyval == ibus_compose_ignore[i])
            return false;
    }

    m_compose_buffer[m_n_compose ++] = keyval;
    m_compose_buffer[m_n_compose] = 0;

    return checkCompactTable (&ibus_compose_table_compact);
}

static int
compare_seq_index (const void *key, const void *value) {
    const uint *keysyms = (const uint *)key;
    const quint16 *seq = (const quint16 *)value;

    if (keysyms[0] < seq[0])
        return -1;
    else if (keysyms[0] > seq[0])
        return 1;
    return 0;
}

static int
compare_seq (const void *key, const void *value) {
    int i = 0;
    const uint *keysyms = (const uint *)key;
    const quint16 *seq = (const quint16 *)value;

    while (keysyms[i]) {
        if (keysyms[i] < seq[i])
            return -1;
        else if (keysyms[i] > seq[i])
            return 1;
        i++;
    }

    return 0;
}


bool
IBusInputContext::checkCompactTable (const IBusComposeTableCompact *table)
{
    qDebug () << "check";
    int row_stride;
    const quint16 *seq_index;
    const quint16 *seq;
    int i;

    /* Will never match, if the sequence in the compose buffer is longer
     * than the sequences in the table.  Further, compare_seq (key, val)
     * will overrun val if key is longer than val. */
    if (m_n_compose > table->max_seq_len)
        return false;

    seq_index = (const quint16 *)bsearch (m_compose_buffer,
                                          table->data, table->n_index_size,
                                          sizeof (quint16) * table->n_index_stride,
                                          compare_seq_index);
    qDebug () << "m_n_compose = " << m_n_compose;
    qDebug () << "seq_index = " << seq_index;

    if (!seq_index) {
        m_compose_buffer[0] = 0;
        m_n_compose = 0;
        return false;
    }

    if (seq_index && m_n_compose == 1) {
        return true;
    }

    seq = NULL;
    for (i = m_n_compose-1; i < table->max_seq_len; i++) {
        row_stride = i + 1;

        if (seq_index[i+1] - seq_index[i] > 0) {
            seq = (const quint16 *) bsearch (m_compose_buffer + 1,
                                             table->data + seq_index[i], (seq_index[i+1] - seq_index[i]) / row_stride,
                                             sizeof (quint16) *  row_stride,
                                             compare_seq);
            qDebug () << "for seq = " << seq;

            if (seq) {
                if (i == m_n_compose - 1)
                    break;
                else {
                    // g_signal_emit_by_name (context_simple, "preedit-changed");
                    return true;
                }
            }
        }
    }

    qDebug () << "seq = " << seq;

    if (!seq) {
        m_compose_buffer[0] = 0;
        m_n_compose = 0;
        return false;
    }
    else
    {
        uint value;
        value = seq[row_stride - 1];
        slotCommitText (new Text (QChar (value)));
        m_compose_buffer[0] = 0;
        m_n_compose = 0;
        return true;
    }
    return false;
}

#endif

void
IBusInputContext::createInputContext (void)
{
    if (!m_context.isNull ()) {
        deleteInputContext ();
    }

    if (!m_bus->isConnected ()) {
        qDebug () << "IBusInputContext::createInputContext:" << "no connection to ibus-daemon";
        return;
    }

    m_context = InputContext::create (m_bus, "Qt");

    if (m_context.isNull ()) {
        qWarning () << "IBusInputContext::createInputContext:" << "create input context failed";
        return;
    }

    /* set capabilities */
    m_context->setCapabilities (m_caps);

    connect (m_context, SIGNAL (commitText (const TextPointer &)),
            this, SLOT (slotCommitText (const TextPointer &)));
    connect (m_context, SIGNAL (updatePreeditText (const TextPointer &, uint, bool)),
            this, SLOT (slotUpdatePreeditText (const TextPointer &, uint, bool)));
    connect (m_context, SIGNAL (showPreeditText (void)),
            this, SLOT (slotShowPreeditText (void)));
    connect (m_context, SIGNAL (hidePreeditText (void)),
            this, SLOT (slotHidePreeditText (void)));

    if (m_has_focus) {
        m_context->focusIn ();
    }
}

void
IBusInputContext::deleteInputContext (void)
{
    /* release context */
    m_context = NULL;
}

void
IBusInputContext::slotCommitText (const TextPointer &text)
{
    if (text.isNull ()) {
        qWarning () << "IBusInputContext::commitText:" << "text == null";
        return;
    }

    QInputMethodEvent event;
    event.setCommitString (text->text ());
    sendEvent (event);
    update ();
}

void
IBusInputContext::displayPreeditText (const TextPointer &text, uint cursor_pos, bool visible)
{
    QList <QAttribute> qattrs;
    QString string;

    if (visible) {
        // append cursor pos
        qattrs.append (QAttribute (QInputMethodEvent::Cursor, cursor_pos, true, 0));

        AttrListPointer attrs = text->attrs ();
        for (uint i = 0; i < attrs->size (); i++) {
            QTextCharFormat format;
            AttributePointer attr = attrs->get (i);
            switch (attr->type ()) {
            case Attribute::TypeUnderline:
                format.setUnderlineStyle (QTextCharFormat::SingleUnderline);
                break;
            case Attribute::TypeForeground:
                format.setForeground (QBrush (QColor (attr->value ())));
                break;
            case Attribute::TypeBackground:
                format.setForeground (QBrush (QColor (attr->value ())));
                break;
            default:
                qWarning () << "IBusInputContext::displayPreeditText:"
                            << "unknow Attribute type" << attr->type ();
                continue;
            }
            qattrs.append (QAttribute (QInputMethodEvent::TextFormat,
                                       attr->start (), attr->length (), QVariant (format)));
        }
        QInputMethodEvent event (text->text (), qattrs);
        sendEvent (event);
    }
    else {
        qattrs.append (QAttribute (QInputMethodEvent::Cursor, 0, true, 0));
        QInputMethodEvent event ("", qattrs);
        sendEvent (event);
    }
    update ();
}

void
IBusInputContext::slotUpdatePreeditText (const TextPointer &text, uint cursor_pos, bool visible)
{
    m_preedit = text;
    m_preedit_visible = visible;
    m_preedit_cursor_pos = cursor_pos;

    displayPreeditText (m_preedit, m_preedit_cursor_pos, visible);
}

void
IBusInputContext::slotShowPreeditText (void)
{
    if (m_preedit_visible)
        return;
    m_preedit_visible = true;
    displayPreeditText (m_preedit, m_preedit_cursor_pos, m_preedit_visible);
}

void
IBusInputContext::slotHidePreeditText (void)
{
    if (!m_preedit_visible)
        return;
    m_preedit_visible = false;
    displayPreeditText (m_preedit, m_preedit_cursor_pos, m_preedit_visible);
}

void
IBusInputContext::slotConnected (void)
{
    displayPreeditText (m_preedit, m_preedit_cursor_pos, false);
    createInputContext ();
}

void
IBusInputContext::slotDisconnected (void)
{
    displayPreeditText (m_preedit, m_preedit_cursor_pos, false);
    deleteInputContext ();
}
