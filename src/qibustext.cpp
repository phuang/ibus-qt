#include "qibustext.h"

namespace IBus {

IBUS_DECLARE_SERIALIZABLE(Text, IBusText);

Text::Text ()
{
    qDebug ("new Text (%p)", this);
}

bool
Text::serialize (QDBusArgument &argument)
{
    if (!Serializable::serialize (argument))
        return false;
    return true;
}

bool
Text::deserialize (QDBusArgument &argument)
{
    if (!Serializable::deserialize (argument))
        return false;
    return true;
}


Text *
Text::copy ()
{
    return NULL;
}

};
