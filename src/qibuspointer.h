#ifndef __Q_IBUS_POINTER_H__
#define __Q_IBUS_POINTER_H__

#include <QObject>
#include <QAtomicInt>

namespace IBus {

template <typename T>
class Pointer
{
public:
    Pointer (T *object = 0) : p (0) {
        set (object);
    }

    Pointer (const Pointer &src) : p (0) {
        set (src.get ());
    }

    template <typename T1>
    Pointer (const Pointer<T1> &src): p (0) {
        set (dynamic_cast<T *> (src.get ()));
    }

    ~Pointer () {
        set (0);
    }

    Pointer &operator= (T *object) {
        set (object);
        return *this;
    }
    
    Pointer &operator= (const Pointer &src) {
        set (src.get ());
        return *this;
    }
    
    template <typename T1>
    Pointer &operator= (const Pointer<T1> &src) {
        set (dynamic_cast<T *> (src.get ()));
        return *this;
    }

    T &operator* () const {
        return *get ();
    }

    T *operator-> () const {
        return get ();
    }

    operator T *() const {
        return get ();
    }

    operator bool () const {
        return !isNull ();
    }

    T *get () const {
        return p;
    }

    bool isNull () const {
        return p == 0;
    }

protected:
    T *p;

    void set (T *object) {
        if (p)
            p->unref ();
        if (object)
            object->ref ();
       p = object;
    }
};

};
#endif
