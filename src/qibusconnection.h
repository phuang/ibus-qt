#ifndef __Q_IBUS_CONNECTION_H__
#define __Q_IBUS_CONNECTION_H__

#include "qibusobject.h"
#include <QDBusConnection>

namespace IBus {

class Connection : public Object
{
    Q_OBJECT

public:
    Connection (const QString &address);
    virtual ~Connection ();

    const QDBusConnection & getConnection () {
        return m_connection;
    }

    bool isConnected () {
    }

private:
    QDBusConnection m_connection;
};

};
#endif
