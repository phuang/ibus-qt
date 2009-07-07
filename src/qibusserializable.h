#ifndef __Q_IBUS_SERIALIZABLE_H_
#define __Q_IBUS_SERIALIZABLE_H_

#include <QDBusArgument>
#include <QHash>

#define INIT_PRIO_HIGH __attribute__((init_priority(1000)))
// #define INIT_PRIO_LOW  __attribute__((init_priority(2000)))
#define INIT_PRIO_LOW

#define IBUS_SERIALIZABLE                               \
private:                                                \
    static QIBusSerializable *newInstance (void);       \
    static QIBusSerializable::Register _register;

#define IBUS_DECLARE_SERIALIZABLE(classname, name)      \
    QIBusSerializable *                                 \
    classname::newInstance (void)                       \
    {                                                   \
        return (QIBusSerializable *) new classname ();  \
    }                                                   \
    QIBusSerializable::Register                         \
    classname::_register INIT_PRIO_LOW (QString(#name), classname::newInstance);


class QIBusSerializable /*  : public QIBusObject */
{

    // Q_OBJECT
    typedef QIBusSerializable *(NEW_FUNC)(void);

protected:
    class Register
    {
    public:
        Register(const QString &name, NEW_FUNC newfn) : classname (name) {
            QIBusSerializable::registerObject (classname, newfn);
        }
        ~Register (void) {
           QIBusSerializable::unregisterObject (classname); 
        }
    private:
        QString classname;
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
    static void registerObject (const QString &name, NEW_FUNC newfn);
    static void unregisterObject (const QString &name);

private:
    static QHash <const QString, NEW_FUNC *> type_table;

    IBUS_SERIALIZABLE
};

#endif
