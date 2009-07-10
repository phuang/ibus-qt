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
    static QIBusSerializable *newInstance (void);       \
    static MetaTypeInfo _info;       \
    virtual const MetaTypeInfo *getMetaInfo (void) const;

#define IBUS_DECLARE_SERIALIZABLE(classname, name)      \
    QIBusSerializable *                                 \
    classname::newInstance (void)                       \
    {                                                   \
        return (QIBusSerializable *) new classname ();  \
    }                                                   \
    const QIBusSerializable::MetaTypeInfo *             \
    classname::getMetaInfo (void) const                 \
    {                                                   \
        return & (classname::_info);                    \
    }                                                   \
    QIBusSerializable::MetaTypeInfo                     \
    classname::_info INIT_PRIO_LOW (QString(#name), classname::newInstance);


class QIBusSerializable /*  : public QIBusObject */
{

    // Q_OBJECT
    typedef QIBusSerializable *(NEW_FUNC)(void);

protected:
    class MetaTypeInfo
    {
    public:
        MetaTypeInfo(const QString &name, NEW_FUNC newfn) : classname (name) {
            QIBusSerializable::registerObject (classname, newfn);
        }
        ~MetaTypeInfo (void) {
           QIBusSerializable::unregisterObject (classname); 
        }
        const QString &getName (void) const {
            return classname;
        }
    private:
        QString classname;
    };

public:
    QIBusSerializable ();
    void setAttachment (const QString &key, QIBusSerializable *value);
    QIBusSerializable *getAttachment (const QString &key);

public:
    virtual bool serialize (QDBusArgument &argument) const;
    virtual bool deserialize (const QDBusArgument &argument);
    virtual QIBusSerializable *copy (const QIBusSerializable *src);

private:
    QMap<QString, QIBusSerializable *> attachments;

/* static */
public:
    static QIBusSerializable *newFromName (const QString &name);
    static QIBusSerializable *newFromDBusArgument (QDBusArgument &argument);
    static bool serializeObject (const QIBusSerializable *obj, QDBusArgument &argument);
    static bool deserializeObject (QIBusSerializable *&obj, const QDBusArgument &argument);
    
    QDBusVariant toVariant (const QIBusSerializable &obj, bool *ok = NULL);
    QIBusSerializable *toObject (const QDBusVariant &variant);
    QIBusSerializable *toObject (const QVariant &variant);

protected:
    static void registerObject (const QString &name, NEW_FUNC newfn);
    static void unregisterObject (const QString &name);

private:
    static QHash<QString, NEW_FUNC *> type_table;

    IBUS_SERIALIZABLE
};

Q_DECLARE_METATYPE(QIBusSerializable)

QDBusArgument& operator<<(QDBusArgument&, const QIBusSerializable &);

#endif
