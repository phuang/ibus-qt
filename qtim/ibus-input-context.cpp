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

typedef QInputMethodEvent::Attribute QAttribute;

IBusInputContext::IBusInputContext (const BusPointer &bus)
    : m_bus (bus),
      m_preedit (NULL),
      m_preedit_visible (false),
      m_has_focus (false),
      m_caps (CapPreeditText | CapFocus)
{
}

IBusInputContext::~IBusInputContext (void)
{
    // client->releaseInputContext (this);
    m_preedit = NULL;
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

    if (widget == NULL) {
        return;
    }

    QRect rect = widget->inputMethodQuery(Qt::ImMicroFocus).toRect ();

    QPoint topleft = widget->mapToGlobal(QPoint(0,0));
    rect.translate (topleft);

    // client->setCursorLocation (this, rect);

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

    if (widget == NULL) {
        m_has_focus = false;
        // client->focusOut (this);
    }
    else {
        /* KateView can not support preedit well. */
        if (widget->inherits("KateViewInternal")) {
            // caps &= ~IBUS_CAP_PREEDIT;
        }
        else {
            // caps |= IBUS_CAP_PREEDIT;
        }
        // client->setCapabilities (this, caps);

        m_has_focus = true;
        // client->focusIn (this);
        update ();
    }
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
bool
IBusInputContext::x11FilterEvent (QWidget *keywidget, XEvent *xevent)
{
#if 0
    if (client->x11FilterEvent (this, keywidget, xevent)) {
            return true;
    }
#endif
    return QInputContext::x11FilterEvent (keywidget, xevent);
}
#endif

void
IBusInputContext::commitText (const TextPointer &text)
{
    QInputMethodEvent event;
    // event.setCommitString (text);
    sendEvent (event);
    update ();
}

void
IBusInputContext::updatePreeditText (const TextPointer &text, uint cursor_pos, bool visible)
{
#if 0
    // qDebug () << text << cursor_pos << show;
    QList <QAttribute> qattrs;

    if (visible) {
        // append cursor pos
        qattrs.append (QAttribute (QInputMethodEvent::Cursor, cursor_pos, true, 0));

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
    }
    else {
        qattrs.append (QAttribute (QInputMethodEvent::Cursor, 0, true, 0));
        text = "";
        cursor_pos = 0;
    }

    preedit_string = text;
    preedit_visible = visible;
    preedit_attrs = attr_list;
    preedit_cursor_pos = cursor_pos;

    QInputMethodEvent event (text, qattrs);
    sendEvent (event);
    update ();
#endif
}

void
IBusInputContext::showPreeditText (void)
{
    if (m_preedit_visible)
        return;

    // updatePreedit (preedit_string, preedit_attrs, preedit_cursor_pos, TRUE);
}

void
IBusInputContext::hidePreeditText (void)
{
    if (!m_preedit_visible)
        return;

    // updatePreedit (preedit_string, preedit_attrs, preedit_cursor_pos, FALSE);
}

