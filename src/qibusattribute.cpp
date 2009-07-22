#include "qibusattribute.h"

namespace IBus {

IBUS_DECLARE_SERIALIZABLE(Attribute, IBusAttribute);

bool
Attribute::serialize (QDBusArgument &argument) const
{
    if (!Serializable::serialize (argument)) {
        return false;
    }

    argument << m_type;
    argument << m_value;
    argument << m_start_index;
    argument << m_end_index;
    return true;
}

bool
Attribute::deserialize (const QDBusArgument &argument)
{
    if (!Serializable::deserialize (argument)) {
        return false;
    }

    argument >> m_type;
    argument >> m_value;
    argument >> m_start_index;
    argument >> m_end_index;
    return true;
}

};
