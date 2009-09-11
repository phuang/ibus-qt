#ifndef __Q_IBUS_CONFIG_H_
#define __Q_IBUS_CONFIG_H_

#include <QDBusConnection>
#include <QDBusVariant>
#include "qibusobject.h"

class IBusConfigAdaptor;

namespace IBus {

class ConfigService;
typedef Pointer<ConfigService> ConfigServicePointer;

class ConfigService : public QObject
{
    Q_OBJECT

public :

    Q_INVOKABLE ConfigService (const QDBusConnection &conn);
    virtual ~ConfigService ();

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
