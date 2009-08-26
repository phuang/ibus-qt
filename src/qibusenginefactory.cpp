#include "qibusenginefactory.h"

namespace IBus {

uint EngineFactory::m_id = 1;

const QDBusObjectPath *EngineFactory::CreateEngine (const QString &engineName)
{
    QMetaObject *p = m_engines[engineName];
    QObject *obj = p->newInstance ();
    IBusEngineAdaptor *adaptor = new IBusEngineAdaptor (obj);
    QString path = "/org/freedesktop/IBus/Engine/" + engineName + "/" + QString::number(m_id);
    ++m_id;

    m_bus->registerObject (path, adaptor);

    QDBusObjectPath *dbusObjPth = new QDBusObjectPath(path);

    return dbusObjPth;
}

void EngineFactory::Destroy()
{}

};
