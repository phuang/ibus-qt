#include "qibusserializable.h"

QIBusSerializable::QIBusSerializable ()
{
}

bool
QIBusSerializable::serialize (QDBusArgument &argument)
{
    return true;
}

bool
QIBusSerializable::deserialize (QDBusArgument &argument)
{
    return true;
}


QIBusSerializable *
QIBusSerializable::copy ()
{
    return NULL;
}
