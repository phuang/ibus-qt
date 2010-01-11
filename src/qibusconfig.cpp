#include <QDBusPendingReply>
#include "qibusconfigproxy.h"
#include "qibusconfig.h"

namespace IBus {

Config::Config (const QDBusConnection &conn): m_conn(conn)
{
    QString service = "org.freedesktop.IBus.Config";
    QString path = "/org/freedesktop/IBus/Config";

    m_config = new IBusConfigProxy(service, path, m_conn);
    if ( !m_config ) {
        qDebug () << "Config::Config, new IBusConfigAdaptor error!";
    }
}

Config::~Config ()
{
    if ( m_config ) {
        delete m_config;
        m_config = NULL;
    }
}

bool
Config::getValue (const QString &section, const QString &name)
{
    QDBusPendingReply<> reply = m_config->GetValue(section, name);
    reply.waitForFinished ();

    if (reply.isError ()) {
        qDebug () << "Config::getValue:" << reply.error ();
        return false;
    }

    return true;
}

bool
Config::setValue (const QString &section, const QString &name, const QDBusVariant &value)
{
    QDBusPendingReply<> reply = m_config->SetValue(section, name, value);
    reply.waitForFinished ();

    if (reply.isError ()) {
        qDebug () << "Config::setValue:" << reply.error ();
        return false;
    }

    return true;
}

bool
Config::unset (const QString &section, const QString &name)
{
    QDBusPendingReply<> reply = m_config->Unset(section, name);
    reply.waitForFinished ();

    if (reply.isError ()) {
        qDebug () << "Config::unset:" << reply.error ();
        return false;
    }

    return true;
}

void
Config::destroy (void)
{
    m_config->Destroy();
}

};
