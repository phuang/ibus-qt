#include "qibusenginefactory.h"

namespace IBus {

const QDBusObjectPath & EngineFactory::CreateEngine(const QString & engineName)
{
    QDBusObjectPath * path = new QDBusObjectPath(engineName);

    m_path = *path;

    return (*path);
}

void EngineFactory::Destroy()
{
    delete &m_path;
}

};
