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
    EngineFactory (const BusPointer &bus):
                                m_bus(bus)
    {}

    ~EngineFactory () {}

public Q_SLOTS: // METHODS
    const QDBusObjectPath *CreateEngine (const QString &engineName);

    /*
    bool addEngine (const QString &name, const QMetaObject *meta_object) {
        m_engines[name] = meta_object;
    }
    */

    void Destroy ();

private :
    static uint    m_id;
    QMap<QString, QMetaObject *> m_engines;
    BusPointer m_bus;
};

};

#endif
