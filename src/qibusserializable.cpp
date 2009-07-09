#include "qibusserializable.h"

QHash<QString, QIBusSerializable::NEW_FUNC*> QIBusSerializable::type_table INIT_PRIO_HIGH;

IBUS_DECLARE_SERIALIZABLE(QIBusSerializable, IBusSerializable);


QIBusSerializable::QIBusSerializable ()
{
    qDebug ("new QIBusSerializable (%p)", this);
}

void
QIBusSerializable::setAttachment (const QString &key, QIBusSerializable *value)
{
    attachments[key] = value;
}

QIBusSerializable *
QIBusSerializable::getAttachment (const QString &key)
{
    return attachments.value (key, NULL);
}

bool
QIBusSerializable::serialize (QDBusArgument &argument) const
{
    QMap<QString, QIBusSerializable *>::const_iterator i;

    argument.beginMap (QVariant::String, QDBusArgument::VariantType);
    for (i = attachments.begin (); i != attachments.end (); i++) {
        argument.beginMapEntry ();
        argument << i.key ();
        QIBusSerializable::serializeObject (i.value (), argument);
        argument.endMapEntry ();
    }
    argument.endMap ();
    return true;
}

bool
QIBusSerializable::deserialize (const QDBusArgument &argument)
{
    argument.beginMap ();
    while (!argument.atEnd()) {
        QString key;
        QIBusSerializable *obj;
        argument.beginMapEntry ();
        argument >> key;
        QIBusSerializable::deserializeObject (obj, argument);
        argument.endMapEntry ();
        attachments[key] = obj;
    }
    argument.endMap ();
    return true;
}


QIBusSerializable *
QIBusSerializable::copy (const QIBusSerializable *src)
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

bool
QIBusSerializable::serializeObject (const QIBusSerializable *obj, QDBusArgument &argument)
{
    argument.beginStructure ();
    argument << obj->getMetaInfo ()->getName ();
    obj->serialize (argument);
    argument.endStructure ();
    return true;
}

QDBusArgument&
operator<<(QDBusArgument &argument, const QIBusSerializable &obj)
{
    QIBusSerializable::serializeObject (&obj, argument);
    return argument;
}

bool
QIBusSerializable::deserializeObject (QIBusSerializable *&obj, const QDBusArgument &argument)
{
    QString name;

    argument.beginStructure ();
    argument >> name;
    obj = QIBusSerializable::newFromName (name);
    obj->deserialize (argument);
    argument.endStructure ();
    return true;
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

