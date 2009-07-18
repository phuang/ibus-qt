#include <QDebug>
#include "qibusobject.h"

namespace IBus {

Object::~Object ()
{
    if (m_referenced && m_refcount != 0) {
        qWarning () << "Object::~Object:" << "Delete an object with refcount != 0";
    }
}

};
