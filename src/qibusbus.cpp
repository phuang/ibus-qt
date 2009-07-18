#include <stdlib.h>
#include <QDebug>
#include <QFile>
#include <QDir>
#include <QList>
#include <QFileSystemWatcher>
#include <QDBusConnection>
#include <dbus/dbus.h>
#include "qibusbus.h"
#include "qibusibusproxy.h"
#include "qibusdbusproxy.h"


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
            this, SLOT (slotAddressChanged (const QString &)));

   open ();
}

Bus::~Bus (void)
{
    if (m_watcher) {
        delete m_watcher;
        m_watcher = NULL;
    }
    reset ();
}

void
Bus::reset (void)
{

    QDBusConnection::disconnectFromBus ("IBus");

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

bool
Bus::open (void)
{
    Q_ASSERT (!isConnected ());

    reset ();

    QString address = getAddress ();
    if (address.isEmpty ()) {
        qWarning () << "Bus::open:" << "Can not get ibus-daemon's address.";
        return false;
    }

    m_connection = new QDBusConnection (
        QDBusConnection::connectToBus (address, "IBus"));

    if (!isConnected ()) {
        qWarning () << "Bus::open:" << "Connect ibus failed!";
        delete m_connection;
        m_connection = NULL;
        return false;
    }

    m_dbus = new DBusProxy ("org.freedesktop.DBus",
                              "/org/freedesktop/DBus",
                              *m_connection);

    m_ibus = new IBusProxy ("org.freedesktop.IBus",
                              "/org/freedesktop/IBus",
                              *m_connection);

    m_connection->connect ("org.freedesktop.DBus.Local",
                           "/org/freedesktop/DBus/Local",
                           "org.freedesktop.DBus.Local",
                           "Disconnected",
                           this,
                           SLOT (slotIBusDisconnected (void)));

    connected ();
    return false;
}

QString
Bus::getSocketPath (void)
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

QString
Bus::getAddress (void)
{
    return "unix:path=/tmp/ibus-phuang/ibus-unix-0";

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

bool
Bus::isConnected (void)
{
    return ((m_connection != NULL) && m_connection->isConnected ());
}

QString
Bus::createInputContext (const QString &name)
{
    if (!isConnected ()) {
        qWarning () << "Bus::createInputContext:" << "IBus is not connected!";
        return NULL;
    }

    QDBusPendingReply<QDBusObjectPath> reply = m_ibus->CreateInputContext (name);
    reply.waitForFinished ();

    if (reply.isError ()) {
        qWarning () << "Bus::createInputContext:" << reply.error ();
        return NULL;
    }

    return reply.value ().path ();
}

bool
Bus::registerComponent (const ComponentPointer &component)
{
    Q_ASSERT (!component.isNull ());

    if (!isConnected ()) {
        qWarning () << "Bus::registerComponent:" << "IBus is not connected!";
        return false;
    }

    QDBusPendingReply<> reply = m_ibus->RegisterComponent (qDBusVariantFromSerializable (component));
    reply.waitForFinished ();

    if (reply.isError ()) {
        qWarning () << "Bus::registerComponent:" << reply.error ();
        return false;
    }

    return true;
}

QList<EngineDescPointer>
Bus::listEngines (void)
{
    QList<EngineDescPointer> engines;

    if (!isConnected ()) {
        qWarning () << "Bus::listEngines:" <<  "IBus is not connected!";
        return engines;
    }

    QDBusPendingReply<QVariantList> reply = m_ibus->ListEngines ();
    reply.waitForFinished ();

    if (reply.isError ()) {
        qWarning () << "Bus::listEngines:" << reply.error ();
        return engines;
    }

    QVariantList ret = reply.value ();
    for (int i = 0; i < ret.size (); i++) {
        EngineDescPointer e;
        ret.at(i).value<QDBusArgument>() >> e;
        engines << e;
    }

    return engines;
}

QList<EngineDescPointer>
Bus::listActiveEngines (void)
{
    QList<EngineDescPointer> engines;

    if (!isConnected ()) {
        qWarning () << "Bus::listActiveEngines:" <<  "IBus is not connected!";
        return engines;
    }

    QDBusPendingReply<QVariantList> reply = m_ibus->ListActiveEngines ();
    reply.waitForFinished ();

    if (reply.isError ()) {
        qWarning () << "Bus::listActiveEngines:" << reply.error ();
        return engines;
    }

    QVariantList ret = reply.value ();
    for (int i = 0; i < ret.size (); i++) {
        EngineDescPointer e;
        ret.at(i).value<QDBusArgument>() >> e;
        engines << e;
    }

    return engines;
}

bool
Bus::exit (bool restart)
{
    if (!isConnected ()) {
        qWarning () << "Bus::exit:" << "IBus is not connected!";
        return false;
    }

    QDBusPendingReply<> reply = m_ibus->Exit (restart);
    reply.waitForFinished ();

    if (reply.isError ()) {
        qWarning () << "Bus::exit:" << reply.error ();
        return false;
    }

    return true;
}

SerializablePointer
Bus::ping (const SerializablePointer &data)
{
    Q_ASSERT (!data.isNull ());

    if (!isConnected ()) {
        qWarning () << "Bus::ping:" <<  "IBus is not connected!";
        return NULL;
    }

    QDBusPendingReply<QDBusVariant> reply = m_ibus->Ping (qDBusVariantFromSerializable (data));
    reply.waitForFinished ();

    if (reply.isError ()) {
        qWarning () << "Bus::ping:" << reply.error ();
        return NULL;
    }

    return qDBusVariantToSerializable (reply.value ());
}

void
Bus::slotAddressChanged (const QString &path)
{
    if (! isConnected ()) {
        open ();
    }
}

void
Bus::slotIBusDisconnected (void)
{
    disconnected ();
    reset ();
}

};
