#include <QDBusPendingReply>
#include "qibusconfigproxy.h"
#include "qibusconfig.h"

namespace IBus {

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

void
Config::destroy (void)
{
    m_config->Destroy();
}

};
