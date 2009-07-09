#include "qibustext.h"

#pragma priority(4000)
IBUS_DECLARE_SERIALIZABLE(QIBusText, IBusText);

QIBusText::QIBusText ()
{
    qDebug ("new QIBusText (%p)", this);
}

bool
QIBusText::serialize (QDBusArgument &argument)
{
    if (!QIBusSerializable::serialize (argument))
        return false;
    return true;
}

bool
QIBusText::deserialize (QDBusArgument &argument)
{
    if (!QIBusSerializable::deserialize (argument))
        return false;
    return true;
}


QIBusText *
QIBusText::copy ()
{
    return NULL;
}
