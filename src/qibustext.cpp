#include "qibustext.h"

namespace IBus {

IBUS_DECLARE_SERIALIZABLE(Text, IBusText);

bool
Text::serialize (QDBusArgument &argument) const
{
    if (!Serializable::serialize (argument))
        return false;
    argument << m_text;
    argument << (SerializablePointer) m_attrs;
    return true;
}

bool
Text::deserialize (const QDBusArgument &argument)
{
    if (!Serializable::deserialize (argument))
        return false;
    argument >> m_text;
    SerializablePointer v;
    argument >> v;
    m_attrs = v;
    return true;
}

};
