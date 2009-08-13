#include "qibusengine.h"

namespace IBus {

Engine::Engine (bool enabled, bool hasFocus)
{
    m_enabled = enabled;
    m_hasFocus = hasFocus;
}

};
