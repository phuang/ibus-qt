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
    EngineFactory (const QString &name, const QDBusConnection &conn):
                    m_engineName(name),
                    m_conn(conn) {}
    ~EngineFactory () {}
public:
    void addEngine (const QString &name, const QMetaObject *metaObject);

private Q_SLOTS:
    bool CreateEngine (const QString &name);
    bool Destroy (const IBusEngineAdaptor *e);

private :

    static uint    m_id;
    QString     m_engineName;

    QMap<QString, const QMetaObject *> m_engineMap;
    QLinkedList<IBusEngineAdaptor *> m_engineLList;
    QDBusConnection m_conn;
};

};

#endif
