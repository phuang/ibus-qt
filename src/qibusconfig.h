#ifndef __Q_IBUS_CONFIG_H_
#define __Q_IBUS_CONFIG_H_

#include <QDBusConnection>
#include <QDBusVariant>
#include "qibusobject.h"

class IBusConfigAdaptor;

namespace IBus {

class Config;
typedef Pointer<Config> ConfigPointer;

class Config : public QObject
{
    Q_OBJECT

public :

    Q_INVOKABLE Config (const QDBusConnection &conn);
    virtual ~Config ();

private :

    // developpers need to implement following functions
    virtual const QDBusVariant &getValue (const QString &section, const QString &name)
    {
        QDBusVariant *retval = new QDBusVariant;
        return *retval;
    }
    virtual void setValue (const QString &section, const QString &name, const QDBusVariant &value)      {}
    virtual void destroy (void)     {}

public :

    Q_INVOKABLE const QDBusVariant &GetValue (const QString &section, const QString &name);
    Q_INVOKABLE void SetValue (const QString &section, const QString &name, const QDBusVariant &value);
    Q_INVOKABLE void Destroy (void);
    
private :

    QDBusConnection     m_conn;
    IBusConfigAdaptor   *m_config;
};

};

#endif
