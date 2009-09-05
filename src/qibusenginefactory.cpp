#include "qibusenginefactory.h"
#include "qibusfactoryadaptor.h"
#include "qibusengine.h"

namespace IBus {

EngineFactory *EngineFactory::m_factory = NULL;

EngineFactory::EngineFactory (const QDBusConnection &conn, uint id)
    : m_conn (conn)
{
    m_id = id;
    m_factoryAdaptor = new IBusFactoryAdaptor (this);
}

EngineFactory::~EngineFactory ()
{
    if ( m_factoryAdaptor != NULL ) {
        delete m_factoryAdaptor;
        m_factoryAdaptor = NULL;
    }

    if ( m_factory != NULL ) {
	    delete m_factory;
	    m_factory = NULL;
    }
}

EngineFactory *EngineFactory::getEngineFactory (const QDBusConnection &conn)
{
    if ( m_factory == NULL ) {
	m_factory = new EngineFactory(conn);
    }

    return m_factory;
}

QString
EngineFactory::createEngine (const QString &engineName)
{
    QString path = "/org/freedesktop/IBus/Engine/" + engineName + "/" + QString::number(++m_id);

    qDebug () << "CreateEngine";
    qDebug () << path;

    if ( !m_engineMap.contains(engineName) ) {
        qDebug () << "EngineFactory::CreateEngine, can not create engine!";
        return "";
    }

    const QMetaObject *mo = m_engineMap[engineName];
    if ( !mo ) {
        qDebug () << "EngineFactory::CreateEngine, QMetaObject pointer in map is null!";
        return "";
    }

    EnginePointer engine = qobject_cast<Engine *>(mo->newInstance (Q_ARG(QString, engineName)));
    if ( engine.isNull() ) {
        qDebug () << "EngineFactory::CreateEngine, newInstance error!";
        return "";
    }

    if ( !m_conn.registerObject (path, engine) ) {
        qDebug () << "EngineFactory::CreateEngine, registerObject error!";
        return "";
    }

    m_engineLList.append(engine);

    return path;
}

QDBusObjectPath
EngineFactory::CreateEngine (const QString &engineName)
{
    return QDBusObjectPath (createEngine (engineName));
}

void
EngineFactory::Destroy ()
{
    delete this;
}

void
EngineFactory::addMetaObject(const QString &name, const QMetaObject *metaObject)
{
    Q_ASSERT(metaObject);

    m_engineMap[name] = metaObject;
}

};
