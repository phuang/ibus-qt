#ifndef __Q_IBUS_FACTORY_ADAPTOR_H_
#define __Q_IBUS_FACTORY_ADAPTOR_H_

#include "qibusbus.h"
#include "qibusengineadaptor.h"
#include "qibusfactoryadaptor.h"

namespace IBus {

class EngineFactory : public Object
{
    Q_OBJECT;

public :
    EngineFactory (const QDBusConnection &conn, uint id = 0):
                    m_id(id),
                    m_conn(conn) {}
    ~EngineFactory () {}

public:
    void addMetaObject (const QString &name, const QMetaObject *metaObject);

private Q_SLOTS:
    Q_INVOKABLE QDBusObjectPath CreateEngine (const QString &name);
    Q_INVOKABLE void Destroy ();

private :

    uint    m_id;
    QDBusConnection m_conn;
    static QMap<QString, const QMetaObject *> m_engineMap;
    static QLinkedList<IBusEngineAdaptor *> m_engineLList;
};

};

#endif
