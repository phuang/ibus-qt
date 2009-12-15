#include <QDebug>
#include "qibusobject.h"

namespace IBus {
/**
 * @brief Destructor of Object
 *
 * @return
 */
Object::~Object ()
{
    if (m_referenced && m_refcount != 0) {
        qWarning () << "Object::~Object:" << "Delete an object with refcount != 0";
    }
}

/**
 * @brief Destroy the object
 *
 * @return
 */
void
Object::destroy ()
{
    delete this;
}

};
