#include "qibuslookuptable.h"

namespace IBus {

IBUS_DECLARE_SERIALIZABLE(LookupTable, IBusLookupTable);

bool
LookupTable::serialize (QDBusArgument &argument) const
{
    if (!Serializable::serialize (argument))
        return false;
    argument << m_text;
    return true;
}

bool
LookupTable::deserialize (const QDBusArgument &argument)
{
    if (!Serializable::deserialize (argument))
        return false;
    argument >> m_text;
    return true;
}

};
