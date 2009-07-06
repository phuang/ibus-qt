#ifndef __Q_IBUS_SERIALIZABLE_H_
#define __Q_IBUS_SERIALIZABLE_H_

#include "qibusobject.h"
#include <QDBusArgument>
#include <QHash>

#define INIT_PRIO_HIGH __attribute__((init_priority(1000)))
#define INIT_PRIO_LOW

#define IBUS_SERIALIZABLE                               \
    private:                                            \
        static QIBusSerializable::Register _register;
#define IBUS_DECLARE_SERIALIZABLE(classname, name)      \
    QIBusSerializable::Register                         \
    classname::_register INIT_PRIO_LOW (QString(#name), &staticMetaObject);
class QIBusSerializable : public QIBusObject
{

    Q_OBJECT

protected:
    class Register
    {
    public:
        Register(const QString &name, const QMetaObject *metaobject) {
            QIBusSerializable::registerObject (name, metaobject);
        }
    };

public:
    Q_INVOKABLE QIBusSerializable ();
    void setAttachment (const QString &key, QIBusSerializable *value);
    QIBusSerializable *getAttachment (const QString &key);


public:
    virtual bool serialize (QDBusArgument &argument);
    virtual bool deserialize (QDBusArgument &argument);
    virtual QIBusSerializable *copy ();

/* static */
public:
    static QIBusSerializable *newFromName (const QString &name);
    static QIBusSerializable *newFromDBusArgument (QDBusArgument &argument);

protected:
    static void registerObject (const QString &name, const QMetaObject *metaobject);

private:
    static QHash <const QString, const QMetaObject *> type_table;

    IBUS_SERIALIZABLE
};

#endif
