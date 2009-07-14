#ifndef __Q_IBUS_OBJECT_H__
#define __Q_IBUS_OBJECT_H__

#include <QObject>
#include <QAtomicInt>

namespace IBus {

template <typename T>
class Pointer
{
    T *p;

    void set (T *object) {
        if (object) {
            
        }
    }
};

class Object : public QObject
{
    Q_OBJECT
    template <typename T> friend class Pointer;

public:
    Object () : m_refcount(0), m_referenced(false) {}
    virtual ~Object () {
        if (m_referenced && m_refcount != 0) {
            qWarning ("Delete an object with refcount != 0");
        }
    }


private:
    Object * ref () {
        m_refcount.ref ();
        return this;
    }

    void unref () {
        if (! m_refcount.deref ()) {
            delete this;
        }
    }

    bool m_referenced;
    QAtomicInt m_refcount;
};

};
#endif
