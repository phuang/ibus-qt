#ifndef __Q_IBUS_SERIALIZABLE_H_
#define __Q_IBUS_SERIALIZABLE_H_

#include <QDBusArgument>
#include <QHash>
#include <QMap>

#define INIT_PRIO_HIGH __attribute__((init_priority(1000)))
// #define INIT_PRIO_LOW  __attribute__((init_priority(2000)))
#define INIT_PRIO_LOW

#define IBUS_SERIALIZABLE                               \
public:                                                 \
    static Serializable *newInstance (void);       \
    static MetaTypeInfo _info;       \
    virtual const MetaTypeInfo *getMetaInfo (void) const;

#define IBUS_DECLARE_SERIALIZABLE(classname, name)      \
    Serializable *                                 \
    classname::newInstance (void)                       \
    {                                                   \
        return (Serializable *) new classname ();  \
    }                                                   \
    const Serializable::MetaTypeInfo *             \
    classname::getMetaInfo (void) const                 \
    {                                                   \
        return & (classname::_info);                    \
    }                                                   \
    Serializable::MetaTypeInfo                     \
    classname::_info INIT_PRIO_LOW (QString(#name), classname::newInstance);

namespace IBus {

class Serializable /*  : public Object */
{
    typedef Serializable *(NEW_FUNC)(void);

protected:
    class MetaTypeInfo
    {
    public:
        MetaTypeInfo(const QString &name, NEW_FUNC newfn) : classname (name) {
            Serializable::registerObject (classname, newfn);
        }
        ~MetaTypeInfo (void) {
           Serializable::unregisterObject (classname); 
        }
        const QString &getName (void) const {
            return classname;
        }
    private:
        QString classname;
    };

public:
    Serializable ();
    void setAttachment (const QString &key, const QVariant &value);
    QVariant getAttachment (const QString &key);

public:
    virtual bool serialize (QDBusArgument &argument) const;
    virtual bool deserialize (const QDBusArgument &argument);
    virtual Serializable *copy (const Serializable *src);

private:
    class PrivateShared {
    public:
        PrivateShared () : ref(1) {}
        QMap<QString, QVariant> attachments;
        QAtomicInt ref;
    };
    PrivateShared *d;

/* static */
public:
    static Serializable *newFromName (const QString &name);
    static Serializable *newFromDBusArgument (QDBusArgument &argument);
    static bool serializeObject (const Serializable *obj, QDBusArgument &argument);
    static bool deserializeObject (Serializable *&obj, const QDBusArgument &argument);
    
    static QDBusVariant toVariant (const Serializable &obj, bool *ok = NULL);
    static Serializable toObject (const QDBusVariant &variant, bool *ok = NULL);
    static Serializable toObject (const QVariant &variant, bool *ok = NULL);

protected:
    static void registerObject (const QString &name, NEW_FUNC newfn);
    static void unregisterObject (const QString &name);

private:
    static QHash<QString, NEW_FUNC *> type_table;

    IBUS_SERIALIZABLE
};

};

Q_DECLARE_METATYPE(IBus::Serializable)
Q_DECLARE_METATYPE(IBus::Serializable *)

#endif
