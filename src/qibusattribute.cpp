#include "qibusattribute.h"

namespace IBus {

IBUS_DECLARE_SERIALIZABLE(Attribute, IBusAttribute);

bool
Attribute::serialize (QDBusArgument &argument) const
{
    if (!Serializable::serialize (argument))
        return false;
    argument << m_text;
    return true;
}

bool
Attribute::deserialize (const QDBusArgument &argument)
{
    if (!Serializable::deserialize (argument))
        return false;
    argument >> m_text;
    return true;
}

};
