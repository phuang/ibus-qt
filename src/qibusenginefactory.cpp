#include "qibusenginefactory.h"
#include "qibusfactoryadaptor.h"

namespace IBus {

EngineFactory::EngineFactory (const QDBusConnection &conn, uint id)
    : m_conn (conn), m_id (id)
{
    m_adaptor = new IBusFactoryAdaptor (this);
}

EngineFactory::~EngineFactory ()
{
    delete m_adaptor;
}

QDBusObjectPath
EngineFactory::CreateEngine (const QString &engineName)
{
    QString path = "/org/freedesktop/IBus/Engine/" + engineName + "/" + QString::number(++m_id);

    if ( !m_engineMap.contains(engineName) ) {
        qDebug () << "EngineFactory::CreateEngine, can not create engine!";
        return QDBusObjectPath();
    }

    const QMetaObject *mo = m_engineMap[engineName];
    if ( !mo ) {
        qDebug () << "EngineFactory::CreateEngine, QMetaObject pointer in map is null!";
        return QDBusObjectPath();
    }

    // QObject::connect(obj, "SIGNAL(destroyed(QObject *))", "SLOT(Destroy (IBusEngineAdaptor *engineAdaptor))");
    // EnginePointer obj = static_cast<EnginePointer >(mo->newInstance (Q_ARG(QString, engineName)));
    Engine *obj = qobject_cast<Engine *>(mo->newInstance (Q_ARG(QString, engineName)));
    if ( !obj ) {
        qDebug () << "EngineFactory::CreateEngine, newInstance error!";
        return QDBusObjectPath();
    }

    IBusEngineAdaptor *adaptor = new IBusEngineAdaptor (obj);
    if ( !adaptor ) {
        qDebug () << "EngineFactory::CreateEngine, new error!";
        return QDBusObjectPath();
    }

    if ( !m_conn.registerObject (path, obj) ) {
        qDebug () << "EngineFactory::CreateEngine, registerObject error!";
        return QDBusObjectPath();
    }

    m_engineLList.append(adaptor);

    qDebug () << path;
    return QDBusObjectPath(path);
}

void
// EngineFactory::Destroy (IBusEngineAdaptor *engineAdaptor)
EngineFactory::Destroy ()
{
    /*
    QLinkedList<IBusEngineAdaptor *>::const_iterator lli = m_engineLList.begin();
    for ( ; lli != m_engineLList.end(); ++lli ) {
        if ( *lli ==  engineAdaptor ) {
            delete engineAdaptor;
            m_engineLList.removeOne(engineAdaptor);

            return;
        }
    }
    */

    return;
}

void
EngineFactory::addMetaObject(const QString &name, const QMetaObject *metaObject)
{
    Q_ASSERT(metaObject);

    m_engineMap[name] = metaObject;
}

};
