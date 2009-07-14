#include "qibustext.h"

namespace IBus {

IBUS_DECLARE_SERIALIZABLE(Text, IBusText);

Text::Text ()
{
    qDebug ("new Text (%p)", this);
}

bool
Text::serialize (QDBusArgument &argument) const
{
    if (!Serializable::serialize (argument))
        return false;
    return true;
}

bool
Text::deserialize (const QDBusArgument &argument)
{
    if (!Serializable::deserialize (argument))
        return false;
    return true;
}

};
