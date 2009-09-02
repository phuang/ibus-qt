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
    EngineFactory (const QDBusConnection &conn, uint id):
                    m_id(id),
                    m_conn(conn) {}
    ~EngineFactory () {}

public:
    void addEngine (const QString &name, const QMetaObject *metaObject);

private Q_SLOTS:
    QDBusObjectPath CreateEngine (const QString &name);
    void Destroy ();

private :

    uint    m_id;
    QDBusConnection m_conn;
    QMap<QString, const QMetaObject *> m_engineMap;
    QLinkedList<IBusEngineAdaptor *> m_engineLList;
};

};

#endif
