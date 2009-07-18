#ifndef __Q_IBUS_OBJECT_H__
#define __Q_IBUS_OBJECT_H__

#include <QObject>
#include <QMetaType>
#include "qibuspointer.h"

#ifdef QT_USE_NAMESPACE
#  undef QT_USE_NAMESPACE
#  define QT_USE_NAMESPACE IBus
#endif

namespace IBus {

class Object;
typedef Pointer <Object> ObjectPointer;

class Object : public QObject
{
    Q_OBJECT
    template <typename T> friend class Pointer;

public:
    Object () : m_refcount(1), m_referenced (false) {}
    virtual ~Object ();

private:
    Object * ref () {
        if (m_referenced) {
            m_refcount.ref ();
        }
        else {
            m_referenced = true;
        }
        return this;
    }

    void unref () {
        if (! m_refcount.deref ()) {
            delete this;
        }
    }

    bool is_referenced () const {
        return m_referenced;
    }

    bool m_referenced;
    QAtomicInt m_refcount;
};

};

Q_DECLARE_METATYPE(IBus::ObjectPointer)

#endif
