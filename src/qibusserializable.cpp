#include "qibusserializable.h"

QHash <const QString, QIBusSerializable::NEW_FUNC*> QIBusSerializable::type_table INIT_PRIO_HIGH;

IBUS_DECLARE_SERIALIZABLE(QIBusSerializable, IBusSerializable);


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

QIBusSerializable *
QIBusSerializable::newFromName(const QString &name)
{
    if (type_table.contains (name)) {
        return type_table[name] ();
    }
    return NULL;    
}

QIBusSerializable *
QIBusSerializable::newFromDBusArgument (QDBusArgument &argument)
{
    
}

void
QIBusSerializable::registerObject (const QString &name, NEW_FUNC newfn)
{
    if (type_table.contains (name)) {
        qFatal ("registerObject failed! name %s has been registered", name.data ());
    }

    if (newfn == NULL) {
        qFatal ("registerObject failed! name = %s, newfn should not be NULL", name.data ());
    }

    QIBusSerializable::type_table[name] = newfn;
}

void
QIBusSerializable::unregisterObject (const QString &name)
{
    if (!type_table.contains (name)) {
        qFatal ("unregisterObject failed! name %s has not been registered", name.data ());
    }
    QIBusSerializable::type_table.remove(name);
}

