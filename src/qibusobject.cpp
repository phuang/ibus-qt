#include "qibusobject.h"
namespace IBus {

Object::~Object ()
{
    if (m_referenced && m_refcount != 0) {
        qWarning ("Delete an object with refcount != 0");
    }
}

};
