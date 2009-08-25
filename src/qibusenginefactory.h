#ifndef __Q_IBUS_FACTORY_ADAPTOR_H_
#define __Q_IBUS_FACTORY_ADAPTOR_H_

#include "qibusfactoryadaptor.h"

namespace IBus {

class EngineFactory : public QObject
{
    Q_OBJECT;

public :
    EngineFactory () {}
    ~EngineFactory () {}

public Q_SLOTS: // METHODS
    const QDBusObjectPath & CreateEngine (const QString &engine_name);
    void Destroy ();

private :
    QDBusObjectPath m_path;

};

};

#endif
