#ifndef __Q_IBUS_SERIALIZABLE_H_
#define __Q_IBUS_SERIALIZABLE_H_

#include "qibusobject.h"
#include <QDBusArgument>
#include <QDBusVariant>
#include <QHash>
#include <QMap>

#define INIT_PRIO_HIGH __attribute__((init_priority(1000)))
// #define INIT_PRIO_LOW  __attribute__((init_priority(2000)))
#define INIT_PRIO_LOW

#define IBUS_SERIALIZABLE                               \
public:                                                 \
    static Serializable *newInstance (void);            \
    static MetaTypeInfo staticMetaTypeInfo;             \
    virtual const MetaTypeInfo *metaTypeInfo (void) const;

#define IBUS_DECLARE_SERIALIZABLE(classname, name)      \
    Serializable *                                      \
    classname::newInstance (void)                       \
    {                                                   \
        return (Serializable *) new classname ();       \
    }                                                   \
    const Serializable::MetaTypeInfo *                  \
    classname::metaTypeInfo (void) const                \
    {                                                   \
        return & (classname::staticMetaTypeInfo);       \
    }                                                   \
    Serializable::MetaTypeInfo                          \
    classname::staticMetaTypeInfo INIT_PRIO_LOW (QString(#name), classname::newInstance);

namespace IBus {

class Serializable;
typedef Pointer<Serializable> SerializablePointer;

QDBusVariant qDBusVariantFromSerializable (const SerializablePointer &p);
SerializablePointer qDBusVariantToSerializable (const QDBusVariant &variant);

class Serializable : public Object
{
    Q_OBJECT;

    template<typename T> friend QDBusArgument& operator<< (QDBusArgument& argument, const Pointer<T> &p);
    template<typename T> friend const QDBusArgument& operator>> (const QDBusArgument& argument, Pointer<T> &p);

    typedef Serializable * (NewInstanceFunc) (void);

protected:
    class MetaTypeInfo
    {
    public:
        MetaTypeInfo(const QString &name, NewInstanceFunc _new) : m_className (name) {
            Serializable::registerObject (m_className, _new);
        }
        ~MetaTypeInfo (void) {
           Serializable::unregisterObject (m_className);
        }
        const QString &className (void) const {
            return m_className;
        }
    private:
        QString m_className;
    };

public:
    Serializable () {}
    void setAttachment (const QString &key, const SerializablePointer &value);
    SerializablePointer getAttachment (const QString &key) const;
    SerializablePointer removeAttachment (const QString &key);

protected:
    virtual bool serialize (QDBusArgument &argument) const;
    virtual bool deserialize (const QDBusArgument &argument);

private:
   QMap <QString, SerializablePointer> m_attachments;

/* static */
protected:
    static void registerObject (const QString &name, NewInstanceFunc _new);
    static void unregisterObject (const QString &name);

private:
    static SerializablePointer createInstance (const QString &name);
    static QHash<QString, NewInstanceFunc *> type_table;

    IBUS_SERIALIZABLE
};

template<typename T>
QDBusArgument& operator<< (QDBusArgument& argument, const Pointer<T> &p)
{
    argument.beginStructure ();
    argument << p->metaTypeInfo ()->className ();
    p->serialize (argument);
    argument.endStructure ();

    return argument;
}

template<typename T>
const QDBusArgument& operator>> (const QDBusArgument& argument, Pointer<T> &p)
{
    Q_ASSERT ((argument.currentType () == QDBusArgument::VariantType) ||
              (argument.currentType () == QDBusArgument::StructureType));

    if (argument.currentType () == QDBusArgument::VariantType) {
        QDBusVariant v;
        argument >> v;
        p = qDBusVariantToSerializable (v);
        return argument;
    }

    if (argument.currentType () == QDBusArgument::StructureType) {
        QString name;
        argument.beginStructure ();
        argument >> name;
        p = Serializable::createInstance (name);
        if (!p.isNull () && !p->deserialize (argument)) {
            p = NULL;
        }
        argument.endStructure ();
        return argument;
    }

    return argument;
}

};

Q_DECLARE_METATYPE (IBus::SerializablePointer);

#endif
