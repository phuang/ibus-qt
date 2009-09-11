#include <QDebug>
#include "qibusconfigservice.h"
#include "qibusconfigadaptor.h"

namespace IBus {

ConfigService::ConfigService (const QDBusConnection &conn) : m_conn(conn)
{
    m_config = new IBusConfigAdaptor(this);
    if ( !m_config ) {
        qDebug () << "ConfigService::ConfigService, new IBusConfigAdaptor error!";
    }
}

ConfigService::~ConfigService ()
{
    if ( NULL != m_config ) {
        delete m_config;
        m_config = NULL;
    }
}

const QDBusVariant &ConfigService::GetValue (const QString &section, const QString &name)
{
    return getValue(section, name);
}

void ConfigService::SetValue (const QString &section, const QString &name, const QDBusVariant &value)
{
    setValue(section, name, value);
}

void ConfigService::Destroy (void)
{
    destroy ();
}

};
