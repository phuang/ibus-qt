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

public :

    virtual void Destroy (void);
    virtual const QDBusVariant &GetValue (const QString &section, const QString &name);
    virtual void SetValue (const QString &section, const QString &name, const QDBusVariant &value);
    
private :

    QDBusConnection     m_conn;
    IBusConfigAdaptor   *m_config;

};

};

#endif
