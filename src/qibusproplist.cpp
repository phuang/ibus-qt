#include "qibusproplist.h"

namespace IBus {

IBUS_DECLARE_SERIALIZABLE(PropList, IBusPropList);

PropList::PropList (void)
{
}

bool
PropList::serialize (QDBusArgument &argument) const
{
    if (!Serializable::serialize (argument))
        return false;
    return true;
}

bool
PropList::deserialize (const QDBusArgument &argument)
{
    if (!Serializable::deserialize (argument))
        return false;
    return true;
}

};
