#ifndef __Q_IBUS_OBJECT_H__
#define __Q_IBUS_OBJECT_H__

#include <QObject>


class QIBusObject : public QObject
{
    Q_OBJECT

public:
    QIBusObject () : ref(0) {};
    

private:
    QAtomicInt ref;
};

#endif
