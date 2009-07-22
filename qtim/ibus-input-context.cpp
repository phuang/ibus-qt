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


typedef QInputMethodEvent::Attribute QAttribute;



IBusInputContext::IBusInputContext (const BusPointer &bus)
    : m_bus (bus),
      m_context (NULL),
      m_preedit (NULL),
      m_preedit_visible (false),
      m_has_focus (false),
      m_caps (CapPreeditText | CapFocus)
{
    Q_ASSERT (!m_bus.isNull ());
    createInputContext ();
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
#ifndef Q_WS_X11
    if (client->filterEvent (this, event)) {
        return true;
    }
    return QInputContext::filterEvent (event);
#else
    return QInputContext::filterEvent (event);
#endif
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
#if 0
    if (client->x11FilterEvent (this, keywidget, xevent)) {
            return true;
    }
#endif

    if (!m_context.isNull ()) {
        uint keyval;
        uint keycode;
        uint state;

        translate_x_key_event (xevent, &keyval, &keycode, &state);
        keycode -= 8;

        return m_context->processKeyEvent (keyval, keycode, state);
    }

    return QInputContext::x11FilterEvent (keywidget, xevent);
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
        QInputMethodEvent event (text->text (), qattrs);
        sendEvent (event);
    #if 0
        // append attributes
        for (QList <QList <quint32> >::iterator it = attr_list.begin (); it != attr_list.end(); ++ it) {

            QList <quint32> attr = *it;
            QTextCharFormat format;

            switch (attr[0]) {
            case 1: // underline
                format.setUnderlineStyle (QTextCharFormat::SingleUnderline);
                break;
            case 2: // foreground
                format.setForeground (QBrush (QColor (attr[1])));
                break;
            case 3: // background
                format.setBackground (QBrush (QColor (attr[1])));
                break;
            default:
                break;
            }

            qattrs.append (QAttribute (QInputMethodEvent::TextFormat, attr[2], attr[3] - attr[2], QVariant (format)));
            // qDebug () << attr[0] << attr[2] << attr[3] - attr[2];
        }
    #endif
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

