#include "qibusproperty.h"

namespace IBus {

IBUS_DECLARE_SERIALIZABLE(Property, IBusProperty);

Property::Property (void)
{
}

bool
Property::serialize (QDBusArgument &argument) const
{
    if (!Serializable::serialize (argument))
        return false;
    argument << m_text;
    return true;
}

bool
Property::deserialize (const QDBusArgument &argument)
{
    if (!Serializable::deserialize (argument))
        return false;
    argument >> m_text;
    return true;
}

};
