#ifndef _Q_IBUS_SERVICE_H_
#define _Q_IBUS_SERVICE_H_

#include "qibusserializable.h"

namespace IBus {

class Service;
typedef Pointer<Service> ServicePointer;

class Service : public QObject
{
    Q_OBJECT;

public:
    Service () {}
    ~Service () {}
};

};

#endif
