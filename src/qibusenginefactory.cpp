#include "qibusenginefactory.h"

namespace IBus {

bool
EngineFactory::CreateEngine (const QString &engineName)
{
    if ( !m_engineMap.contains(engineName) ) {
        qDebug () << "EngineFactory::CreateEngine, can not create engine!";
        return false;
    }

    QString path = "/org/freedesktop/IBus/Engine/" + engineName + "/" + QString::number(++m_id);

    const QMetaObject *mo = m_engineMap[engineName];
    if ( !mo ) {
        qDebug () << "EngineFactory::CreateEngine, QMetaObject pointer in map is null!";
        return false;
    }

    Engine *obj = qobject_cast<Engine *>(mo->newInstance (Q_ARG(QString, engineName)));

    if ( !obj ) {
        qDebug () << "EngineFactory::CreateEngine, newInstance error!";
        return false;
    }

    IBusEngineAdaptor *adaptor = new IBusEngineAdaptor (obj);
    if ( !adaptor ) {
        qDebug () << "EngineFactory::CreateEngine, new error!";
        return false;
    }

    if ( !m_conn.registerObject (path, adaptor) ) {
        qDebug () << "EngineFactory::CreateEngine, registerObject error!";
        return false;
    }

    m_engineLList.append(adaptor);

    return true;
}

void
EngineFactory::addEngine (const QString &name, const QMetaObject *metaObject)
{
    m_engineMap[name] = metaObject;
}

bool
EngineFactory::Destroy (IBusEngineAdaptor *engineAdaptor)
{
    QLinkedList<IBusEngineAdaptor *>::const_iterator lli = m_engineLList.begin();
    for ( ; lli != m_engineLList.end(); ++lli ) {
        if ( *lli ==  engineAdaptor ) {
            delete engineAdaptor;
            m_engineLList.removeOne(engineAdaptor);

            return true;
        }
    }

    return false;
}

};
