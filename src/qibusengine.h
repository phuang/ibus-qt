#ifndef _Q_IBUS_ENGINE_H_
#define _Q_IBUS_ENGINE_H_

#include <QMetaType>
#include "qibuspointer.h"

namespace IBus {

class Engine;
typedef Pointer<Engine> EnginePointer;

class Engine
{
public:
    Engine () {}
    Engine (bool enabled, bool hasFocus);
    ~Engine () {}

private:
    bool m_enabled;
    bool m_hasFocus;
};

};

#endif
