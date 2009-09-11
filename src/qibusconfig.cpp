#include <QDebug>
#include "qibusconfig.h"
#include "qibusconfigadaptor.h"

namespace IBus {

Config::Config (const QDBusConnection &conn) : m_conn(conn)
{
    m_config = new IBusConfigAdaptor(this);
    if ( !m_config ) {
        qDebug () << "Config::Config, new IBusConfigAdaptor error!";
    }
}

Config::~Config ()
{
    if ( NULL != m_config ) {
        delete m_config;
        m_config = NULL;
    }
}

const QDBusVariant &Config::GetValue (const QString &section, const QString &name)
{
    QDBusVariant *retval = new QDBusVariant;
    return *retval;
}

void Config::SetValue (const QString &section, const QString &name, const QDBusVariant &value) {}
void Config::Destroy (void) {}

};
