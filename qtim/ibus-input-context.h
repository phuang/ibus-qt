/* vim:set noet ts=4: */
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
#ifndef __IBUS_INPUT_CONTEXT_H_
#define __IBUS_INPUT_CONTEXT_H_
#include <QInputContext>
#include <QList>
#include <qibusinputcontext.h>

using namespace IBus;

class IBusInputContext : public QInputContext  {
	Q_OBJECT
public:
	IBusInputContext (const BusPointer &bus);
	~IBusInputContext ();

public:
	bool filterEvent (const QEvent *event);
	QFont font (void) const;
	QString identifierName (void);
	bool isComposing (void) const;
	QString language (void);
	void mouseHandler (int x, QMouseEvent *event);
	void reset (void);
	void update (void);
	void setFocusWidget (QWidget *widget );
	void widgetDestroyed (QWidget *widget);
#ifdef Q_WS_X11
	bool x11FilterEvent (QWidget *keywidget, XEvent *event);
#endif

	void commitText (const TextPointer &text);
	void updatePreeditText (const TextPointer &text, uint cursor_pos, bool visible);
	void showPreeditText (void);
	void hidePreeditText (void);

private slots:

private:
	BusPointer m_bus;
	TextPointer m_preedit;
	uint m_preedit_cursor_pos;
	bool m_preedit_visible;
	uint m_caps;
	bool m_has_focus;
};

#endif //__IBUS_INPUT_CONTEXT_H_
