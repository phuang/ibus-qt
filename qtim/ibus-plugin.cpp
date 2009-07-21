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
#include <QInputContextPlugin>
#include <qibusbus.h>
#include "ibus-input-context.h"

#define IBUS_IDENTIFIER_NAME "ibus"

using namespace IBus;

/* The class Definition */
class IBusPlugin: public QInputContextPlugin
{

private:
    /**
     * The language list for SCIM.
     */
    static QStringList ibus_languages;

public:

    IBusPlugin (QObject *parent = 0);

    ~IBusPlugin ();

    QStringList keys () const;

    QStringList languages (const QString &key);

    QString description (const QString &key);

    QInputContext *create (const QString &key);

    QString displayName (const QString &key);

private:
    BusPointer m_bus;

};


/* Implementations */
QStringList IBusPlugin::ibus_languages;


IBusPlugin::IBusPlugin (QObject *parent)
    :QInputContextPlugin (parent)
{
}


IBusPlugin::~IBusPlugin ()
{
}

QStringList
IBusPlugin::keys () const
{
    QStringList identifiers;
    identifiers.push_back (IBUS_IDENTIFIER_NAME);
    return identifiers;
}


QStringList
IBusPlugin::languages (const QString & key)
{
    if (key.toLower () != IBUS_IDENTIFIER_NAME) {
        return QStringList ();
    }

    if (ibus_languages.empty ()) {
        ibus_languages.push_back ("zh");
        ibus_languages.push_back ("ja");
        ibus_languages.push_back ("ko");
    }
    return ibus_languages;
}


QString
IBusPlugin::description (const QString &key)
{
    if (key.toLower () != IBUS_IDENTIFIER_NAME) {
        return QString ("");
    }

    return QString::fromUtf8 ("Qt immodule plugin for IBus");
}


QInputContext *
IBusPlugin::create (const QString &key)
{
    if (key.toLower () != IBUS_IDENTIFIER_NAME) {
        return NULL;
    }

    if (m_bus.isNull ()) {
        m_bus = new Bus ();
    }
    return static_cast<QInputContext *> (new IBusInputContext (m_bus));
}


QString IBusPlugin::displayName (const QString &key)
{
    return key;
}

Q_EXPORT_PLUGIN2 (IBusPlugin, IBusPlugin)
