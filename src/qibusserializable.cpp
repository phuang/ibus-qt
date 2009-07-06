#include "qibusserializable.h"

QHash <const QString, const QMetaObject*> QIBusSerializable::type_table INIT_PRIO_HIGH;

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
        return qobject_cast <QIBusSerializable *> (type_table[name]->newInstance ());
    }
    return NULL;    
}

QIBusSerializable *
QIBusSerializable::newFromDBusArgument (QDBusArgument &argument)
{
    
}

void
QIBusSerializable::registerObject (const QString &name, const QMetaObject *metaobject)
{
    if (type_table.contains (name)) {
        qFatal ("registerObject failed! name %s has been registered", name.data ());
    }

    if (metaobject == NULL) {
        qFatal ("registerObject failed! name = %s, metaobject should not be NULL", name.data ());
    }

    QIBusSerializable::type_table[name] = metaobject;
}

