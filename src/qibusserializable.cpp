#include "qibusserializable.h"

namespace IBus {

QHash<QString, Serializable::NEW_FUNC*> Serializable::type_table INIT_PRIO_HIGH;

IBUS_DECLARE_SERIALIZABLE(Serializable, IBusSerializable);


Serializable::Serializable ()
{
    d = new PrivateShared ();
}

void
Serializable::setAttachment (const QString &key, const QVariant &value)
{
    d->attachments[key] = value;
}

QVariant
Serializable::getAttachment (const QString &key)
{
    if (d->attachments.contains (key)) {
        return d->attachments.value (key);
    }

    return QVariant ();
}

bool
Serializable::serialize (QDBusArgument &argument) const
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
Serializable::deserialize (const QDBusArgument &argument)
{
    argument.beginMap ();
    while (!argument.atEnd()) {
        QString key;
        Serializable *obj;
        argument.beginMapEntry ();
        argument >> key;
        Serializable::deserializeObject (obj, argument);
        argument.endMapEntry ();
        d->attachments[key] = qVariantFromValue (obj);
        delete obj;
    }
    argument.endMap ();
    return true;
}


Serializable *
Serializable::copy (const Serializable *src)
{
    return NULL;
}

Serializable *
Serializable::newFromName(const QString &name)
{
    if (type_table.contains (name)) {
        return type_table[name] ();
    }
    return NULL;
}

Serializable *
Serializable::newFromDBusArgument (QDBusArgument &argument)
{

}

bool
Serializable::serializeObject (const Serializable *obj, QDBusArgument &argument)
{
    argument.beginStructure ();
    argument << obj->getMetaInfo ()->getName ();
    obj->serialize (argument);
    argument.endStructure ();
    return true;
}

bool
Serializable::deserializeObject (Serializable *&obj, const QDBusArgument &argument)
{
    QString name;

    argument.beginStructure ();
    argument >> name;
    obj = Serializable::newFromName (name);
    obj->deserialize (argument);
    argument.endStructure ();
    return true;
}


QDBusVariant  
Serializable::toVariant (const Serializable & obj, bool *ok)
{
    QDBusArgument argument;
    
    argument.beginStructure ();
    argument << obj.getMetaInfo ()->getName ();
    obj.serialize (argument);
    argument.endStructure ();

    return QDBusVariant (QVariant::fromValue (argument));

}

Serializable
Serializable::toObject (const QDBusVariant & variant, bool *ok)
{
    return Serializable();
}

Serializable
Serializable::toObject (const QVariant & variant, bool *ok)
{
    return Serializable();
}

void
Serializable::registerObject (const QString &name, NEW_FUNC newfn)
{
    if (type_table.contains (name)) {
        qFatal ("registerObject failed! name %s has been registered", name.data ());
    }

    if (newfn == NULL) {
        qFatal ("registerObject failed! name = %s, newfn should not be NULL", name.data ());
    }

    Serializable::type_table[name] = newfn;
}

void
Serializable::unregisterObject (const QString &name)
{
    if (!type_table.contains (name)) {
        qFatal ("unregisterObject failed! name %s has not been registered", name.data ());
    }
    Serializable::type_table.remove(name);
}

};
