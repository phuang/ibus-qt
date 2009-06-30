#include "qibusserializable.h"

QIBusSerializable::QIBusSerializable ()
{
    qDebug ("new QIBusSerializable (%p)", this);
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
