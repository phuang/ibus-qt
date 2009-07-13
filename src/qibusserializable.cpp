#include "qibusserializable.h"

QHash<QString, QIBusSerializable::NEW_FUNC*> QIBusSerializable::type_table INIT_PRIO_HIGH;

IBUS_DECLARE_SERIALIZABLE(QIBusSerializable, IBusSerializable);


QIBusSerializable::QIBusSerializable ()
{
    d = new PrivateShared ();
}

void
QIBusSerializable::setAttachment (const QString &key, const QVariant &value)
{
    d->attachments[key] = value;
}

QVariant
QIBusSerializable::getAttachment (const QString &key)
{
    if (d->attachments.contains (key)) {
        return d->attachments.value (key);
    }

    return QVariant ();
}

bool
QIBusSerializable::serialize (QDBusArgument &argument) const
{
    QMap<QString, QVariant>::const_iterator i;

    argument.beginMap (QVariant::String, QDBusArgument::VariantType);
    for (i = d->attachments.begin (); i != d->attachments.end (); i++) {
        argument.beginMapEntry ();
        argument << i.key ();
        argument << QDBusVariant (i.value ());
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
        d->attachments[key] = qVariantFromValue (obj);
        delete obj;
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


QDBusVariant  
QIBusSerializable::toVariant (const QIBusSerializable & obj, bool *ok)
{
    QDBusArgument argument;
    
    argument.beginStructure ();
    argument << obj.getMetaInfo ()->getName ();
    obj.serialize (argument);
    argument.endStructure ();

    return QDBusVariant (QVariant::fromValue (argument));

}

QIBusSerializable
QIBusSerializable::toObject (const QDBusVariant & variant, bool *ok)
{
    return QIBusSerializable();
}

QIBusSerializable
QIBusSerializable::toObject (const QVariant & variant, bool *ok)
{
    return QIBusSerializable();
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

