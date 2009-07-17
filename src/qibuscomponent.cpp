#include "qibuscomponent.h"

namespace IBus {

IBUS_DECLARE_SERIALIZABLE(Component, IBusComponent);

Component::Component (void)
{
}

bool
Component::serialize (QDBusArgument &argument) const
{
    if (!Serializable::serialize (argument))
        return false;
    argument << m_text;
    return true;
}

bool
Component::deserialize (const QDBusArgument &argument)
{
    if (!Serializable::deserialize (argument))
        return false;
    argument >> m_text;
    return true;
}

};
