#include "qibusenginefactory.h"

namespace IBus {

const QDBusObjectPath & EngineFactory::CreateEngine(const QString & engineName)
{
    m_path = new QDBusObjectPath(engineName);

    return (*m_path);
}

void EngineFactory::Destroy()
{
    delete m_path;
}

};
