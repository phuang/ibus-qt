#ifndef __Q_IBUS_CONNECTION_H__
#define __Q_IBUS_CONNECTION_H__

#include "qibusobject.h"
#include <QDBusConnection>

class QIBusConnection : public QIBusObject
{
    Q_OBJECT

public:
    QIBusConnection (const QString &address);
    virtual ~QIBusConnection ();

    const QDBusConnection & getConnection () {
        return connection;
    }

private:
    QDBusConnection connection;
};

#endif
