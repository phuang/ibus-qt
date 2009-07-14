#include "qibusserializable.h"
#include <QDebug>

namespace IBus {

QHash<QString, Serializable::NewInstanceFunc *> Serializable::type_table INIT_PRIO_HIGH;

IBUS_DECLARE_SERIALIZABLE(Serializable, IBusSerializable);


    SerializablePointer &removeAttachment (const QString &key);

void
Serializable::setAttachment (const QString &key, const SerializablePointer &value)
{
    m_attachments[key] = value;
}

SerializablePointer
Serializable::getAttachment (const QString &key) const
{
    SerializablePointer p;
    if (m_attachments.contains (key))
        p = m_attachments.value (key);
    return p;
}

SerializablePointer
Serializable::removeAttachment (const QString &key)
{
    SerializablePointer p = m_attachments.value (key, p);
    if (p)
        m_attachments.remove (key);
    return p;
}

bool
Serializable::serialize (QDBusArgument &argument) const
{
    QMap<QString, SerializablePointer>::const_iterator i;

    argument.beginMap (QVariant::String, QDBusArgument::VariantType);
    for (i = m_attachments.begin (); i != m_attachments.end (); i++) {
        argument.beginMapEntry ();
        argument << i.key ();
        argument << i.value ();
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
        SerializablePointer p;
        argument.beginMapEntry ();
        argument >> key;
        argument >> p;
        argument.endMapEntry ();
        m_attachments[key] = p;
    }
    argument.endMap ();
    return true;
}

SerializablePointer
Serializable::createInstance(const QString &name)
{
    SerializablePointer p;

    if (type_table.contains (name)) {
        p = type_table[name]();
    }
    return p;
}

void
Serializable::registerObject (const QString &name, NewInstanceFunc _new)
{
    if (type_table.contains (name)) {
        qFatal ("registerObject failed! name %s has been registered", name.data ());
    }

    if (_new == NULL) {
        qFatal ("registerObject failed! _new should not be NULL");
    }

    Serializable::type_table[name] = _new;
}

void
Serializable::unregisterObject (const QString &name)
{
    if (!type_table.contains (name)) {
        qFatal ("unregisterObject failed! name %s has not been registered", name.data ());
    }
    Serializable::type_table.remove(name);
}

QDBusArgument&
operator<< (QDBusArgument& argument, const SerializablePointer &p)
{
    argument.beginStructure ();
    argument << p->getMetaInfo ()->getName ();
    p->serialize (argument);
    argument.endStructure ();

    return argument;
}

const QDBusArgument&
operator>> (const QDBusArgument& argument, SerializablePointer &p)
{
    QString name = "AAA";

    argument.beginStructure ();
    argument >> name;
    p = Serializable::createInstance (name);
    p->deserialize (argument);
    argument.endStructure ();

    return argument;
}


QDBusVariant
qDBusVariantFromSerializable (const SerializablePointer &p)
{
    QDBusArgument argument;
    argument << p;
    return QDBusVariant (qVariantFromValue (argument));
}


SerializablePointer
qDBusVariantToSerializable (const QDBusVariant &variant)
{
    SerializablePointer p;
    QDBusArgument argument;

    argument = variant.variant().value<QDBusArgument> ();
    argument >> p;

    return p;
}

};
