#ifndef __Q_IBUS_CONFIG_H_
#define __Q_IBUS_CONFIG_H_

#include <QDBusConnection>
#include <QDBusVariant>
#include "qibusobject.h"

class IBusConfigProxy;

namespace IBus {

class Config : public QObject
{
    Q_OBJECT

public :
    Config (const QDBusConnection &conn);
    virtual ~Config ();

public :

    bool getValue (const QString &section, const QString &name);    // need to process return value;
    bool setValue (const QString &section, const QString &name, const QDBusVariant &value);
    void destroy (void);

private :

    QDBusConnection m_conn;
    IBusConfigProxy *m_config;
};

};

#endif
