#include "qibusenginefactory.h"

namespace IBus {

uint EngineFactory::m_id = 0;

bool EngineFactory::CreateEngine (const QString &engineName)
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

    QObject *obj = mo->newInstance (Q_ARG(QString, engineName), Q_ARG(QString, path), Q_ARG(QDBusConnection, m_conn));
    if ( !obj ) {
        qCritical () << "EngineFactory::CreateEngine, newInstance error!";
        return false;
    }

    IBusEngineAdaptor *adaptor = new IBusEngineAdaptor (obj);
    if ( !adaptor ) {
        qCritical () << "EngineFactory::CreateEngine, new error!";
        return false;
    }

    if ( !m_conn.registerObject (path, adaptor) ) {
        qCritical () << "EngineFactory::CreateEngine, registerObject error!";
        return false;
    }

    m_engineLList.append(adaptor);

    return true;
}

void EngineFactory::addEngine (const QString &name, const QMetaObject *metaObject)
{
    m_engineMap[name] = metaObject;
}

bool EngineFactory::Destroy(const IBusEngineAdaptor *engineAdaptor)
{
    QLinkedList<IBusEngineAdaptor *>::const_iterator lli = m_engineLList.begin();
    for ( ; lli != m_engineLList.end(); ++lli ) {
        if ( *lli ==  engineAdaptor ) {
            delete engineAdaptor;
            return true;
        }
    }

    return false;

}

};
