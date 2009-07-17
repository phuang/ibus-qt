#include "qibusenginedesc.h"

namespace IBus {

IBUS_DECLARE_SERIALIZABLE(EngineDesc, IBusEngineDesc);

EngineDesc::EngineDesc (void)
{
}

bool
EngineDesc::serialize (QDBusArgument &argument) const
{
    if (!Serializable::serialize (argument))
        return false;
    argument << m_text;
    return true;
}

bool
EngineDesc::deserialize (const QDBusArgument &argument)
{
    if (!Serializable::deserialize (argument))
        return false;
    argument >> m_text;
    return true;
}

};
