#include <sys/types.h>
#include <signal.h>
#include <stdlib.h>
#include <QDebug>
#include <QFile>
#include <QFileInfo>
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
: m_connection (NULL),
  m_dbus (NULL),
  m_ibus (NULL)
{
    QFileInfo file (getSocketPath ());

    m_watcher.addPath (file.path ());
    if (file.exists ()) {
        m_watcher.addPath (file.filePath ());
    }

    QObject::connect (&m_watcher, SIGNAL (fileChanged (const QString &)),
            this, SLOT (slotAddressChanged (const QString &)));
    QObject::connect (&m_watcher, SIGNAL (directoryChanged (const QString &)),
            this, SLOT (slotAddressChanged (const QString &)));

    open ();
}

Bus::~Bus (void)
{
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
    QStringList strs = display.split(":");
    QString hostname = "unix";
    QString display_number = "0";

    if (!strs[0].isEmpty())
        hostname = strs[0];
    strs = strs[1].split(".");
    if (!strs[0].isEmpty())
        display_number = strs[0];

    QString path =
        QDir::homePath() +
        QDir::separator() + ".ibus" +
        QDir::separator() + "bus" +
        QDir::separator() +
        dbus_get_local_machine_id () +
        "-" + hostname + "-" + display_number;

    return path;
}

QString
Bus::getAddress (void)
{
    QString address;
    pid_t pid = -1;

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
            continue;
        }

        if (line.startsWith ("IBUS_DAEMON_PID=")) {
            bool ok = false;
            pid = line.mid (sizeof ("IBUS_DAEMON_PID=") - 1).toInt (&ok);
            if (!ok)
                pid = -1;
            continue;
        }
    }

    if (pid == -1 || kill (pid, 0) != 0)
        address = "";

    return address;
}

bool
Bus::isConnected (void)
{
    return ((m_connection != NULL) && m_connection->isConnected ());
}

QString
Bus::hello (void)
{
    if (!isConnected ()) {
        qWarning () << "Bus::hello:" << "IBus is not connected!";
        return NULL;
    }

    QDBusPendingReply<QString> reply = m_dbus->Hello ();
    reply.waitForFinished ();

    if (reply.isError ()) {
        qWarning () << "Bus::hello:" << reply.error ();
        return NULL;
    }

    return reply;
}

void
Bus::addMatch (const QString &rule)
{
    if (!isConnected ()) {
        qWarning () << "Bus::addMatch:" << "IBus is not connected!";
        return;
    }

    QDBusPendingReply<> reply = m_dbus->AddMatch (rule);
    reply.waitForFinished ();

    if (reply.isError ()) {
        qWarning () << "Bus::addMatch:" << reply.error ();
        return;
    }
}

void
Bus::removeMatch (const QString &rule)
{
    if (!isConnected ()) {
        qWarning () << "Bus::removeMatch:" << "IBus is not connected!";
        return;
    }

    QDBusPendingReply<> reply = m_dbus->RemoveMatch (rule);
    reply.waitForFinished ();

    if (reply.isError ()) {
        qWarning () << "Bus::removeMatch:" << reply.error ();
        return;
    }
}

QString
Bus::getId (void)
{
    if (!isConnected ()) {
        qWarning () << "Bus::getId:" << "IBus is not connected!";
        return NULL;
    }

    QDBusPendingReply<QString> reply = m_dbus->GetId ();
    reply.waitForFinished ();

    if (reply.isError ()) {
        qWarning () << "Bus::getId:" << reply.error ();
        return NULL;
    }

    return reply;
}

QString
Bus::getNameOwner (const QString &name)
{
    if (!isConnected ()) {
        qWarning () << "Bus::getNameOwner:" << "IBus is not connected!";
        return NULL;
    }

    QDBusPendingReply<QString> reply = m_dbus->GetNameOwner (name);
    reply.waitForFinished ();

    if (reply.isError ()) {
        qWarning () << "Bus::getNameOwner:" << reply.error ();
        return NULL;
    }

    return reply;
}

QStringList
Bus::listNames (void)
{
    if (!isConnected ()) {
        qWarning () << "Bus::listNames:" << "IBus is not connected!";
        return QStringList ();
    }

    QDBusPendingReply<QStringList> reply = m_dbus->ListNames ();
    reply.waitForFinished ();

    if (reply.isError ()) {
        qWarning () << "Bus::listNames:" << reply.error ();
        return QStringList ();
    }

    return reply;
}

bool
Bus::nameHasOwner (const QString &name)
{
    if (!isConnected ()) {
        qWarning () << "Bus::nameHasOwner:" << "IBus is not connected!";
        return false;
    }

    QDBusPendingReply<bool> reply = m_dbus->NameHasOwner (name);
    reply.waitForFinished ();

    if (reply.isError ()) {
        qWarning () << "Bus::nameHasOwner:" << reply.error ();
        return false;
    }

    return reply;
}

uint
Bus::requestName (const QString &name, uint flag)
{
    if (!isConnected ()) {
        qWarning () << "Bus::requestName:" << "IBus is not connected!";
        return 0;
    }

    QDBusPendingReply<uint> reply = m_dbus->RequestName (name, flag);
    reply.waitForFinished ();

    if (reply.isError ()) {
        qWarning () << "Bus::requestName:" << reply.error ();
        return 0;
    }

    return reply;
}

uint
Bus::releaseName (const QString &name)
{
    if (!isConnected ()) {
        qWarning () << "Bus::releaseName:" << "IBus is not connected!";
        return 0;
    }

    QDBusPendingReply<uint> reply = m_dbus->ReleaseName (name);
    reply.waitForFinished ();

    if (reply.isError ()) {
        qWarning () << "Bus::releaseName:" << reply.error ();
        return 0;
    }

    return reply;
}

/* org.freedesktop.IBus methods */
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

    QDBusVariant variant;

    if (!isConnected ()) {
        qWarning () << "Bus::registerComponent:" << "IBus is not connected!";
        return false;
    }

    QDBusPendingReply<> reply = m_ibus->RegisterComponent (qDBusVariantFromSerializable (component, variant));
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

    QDBusVariant variant;

    if (!isConnected ()) {
        qWarning () << "Bus::ping:" <<  "IBus is not connected!";
        return NULL;
    }

    QDBusPendingReply<QDBusVariant> reply = m_ibus->Ping (qDBusVariantFromSerializable (data, variant));
    reply.waitForFinished ();

    if (reply.isError ()) {
        qWarning () << "Bus::ping:" << reply.error ();
        return NULL;
    }

    return qDBusVariantToSerializable<Serializable> (reply.value ());
}

void
Bus::slotAddressChanged (const QString &path)
{
    QFileInfo file(getSocketPath ());

    if (file.exists ()) {
        if (m_watcher.files ().indexOf (file.filePath ()) == -1)
            m_watcher.addPath (getSocketPath ());
        if (! isConnected ()) {
            open ();
        }
    }
}

void
Bus::slotIBusDisconnected (void)
{
    disconnected ();
    reset ();
}

};
