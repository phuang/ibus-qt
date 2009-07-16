#include <stdlib.h>
#include <QFile>
#include <QDir>
#include <QFileSystemWatcher>
#include <QDBusConnection>
#include <QDebug>
#include <dbus/dbus.h>
#include "qibusbus.h"
#include "qibusibusadaptor.h"
#include "qibusdbusadaptor.h"


namespace IBus {

Bus::Bus (void)
: m_watcher (NULL),
  m_connection (NULL), 
  m_dbus (NULL),
  m_ibus (NULL)
{

   QString path = getSocketPath ();
   m_watcher = new QFileSystemWatcher ();
   m_watcher->addPath (path);

   QObject::connect (m_watcher, SIGNAL (fileChanged (const QString &)),
            this, SLOT (addressChanged (const QString &)));
}

Bus::~Bus (void)
{
    if (m_watcher) {
        delete m_watcher;
        m_watcher = NULL;
    }
    reset ();
}

void Bus::reset (void)
{
    if (m_connection) {
        delete m_connection;
        m_connection = NULL;
    }
    if (m_dbus) {
        delete m_dbus;
        m_dbus = NULL;
    }
    if (m_ibus) {
        delete m_ibus;
        m_ibus = NULL;
    }
}

bool Bus::connect (void)
{
    return false;
}

QString Bus::getSocketPath (void)
{
    QString display = getenv ("DISPLAY");

    QString path = 
        QDir::homePath() +
        QDir::separator() + ".config" +
        QDir::separator() + "ibus" +
        QDir::separator() + "bus" +
        QDir::separator() +
        dbus_get_local_machine_id () +
        "-unix-0";

    return path;
}

QString Bus::getAddress (void)
{
    QString address;
    QString path = getSocketPath ();

    QFile file(path);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return address;

    while (!file.atEnd ()) {
        QString line(file.readLine ());
        line = line.trimmed ();
        if (line.startsWith ("#"))
            continue;

        if (line.startsWith ("IBUS_ADDRESS=")) {
            address = line.mid (sizeof ("IBUS_ADDRESS=") -1);
            break;
        }
    }

    return address;
}

bool Bus::isConnected (void)
{
    return ((m_connection != NULL) && m_connection->isConnected ());
}

void Bus::addressChanged (const QString &path)
{
    qDebug () << "address changed" << path << "address = " << getAddress ();
}

};
