#include "qibusattribute.h"

namespace IBus {

IBUS_DECLARE_SERIALIZABLE(Attribute, IBusAttribute);

bool
Attribute::serialize (QDBusArgument &argument) const
{
    if (!Serializable::serialize (argument))
        return false;
    argument << m_type;
    argument << m_value;
    argument << m_start_index;
    argument << m_end_index;
    return true;
}

bool
Attribute::deserialize (const QDBusArgument &argument)
{
    if (!Serializable::deserialize (argument))
        return false;
    argument >> m_type;
    argument >> m_value;
    argument >> m_start_index;
    argument >> m_end_index;
    return true;
}

void
Attribute::attribute_underline( uint type, uint start, uint end)
{
    m_type = 1;
    m_value = type;
    m_start_index = start;
    m_end_index = end;
}

void
Attribute::attribute_foreground( uint color, uint start, uint end)
{
    m_type = 2;
    m_value = color;
    m_start_index = start;
    m_end_index = end;
}

void
Attribute::attribute_foreground( uint color, uint start, uint end)
{
    m_type = 3;
    m_value = color;
    m_start_index = start;
    m_end_index = end;
}

};
