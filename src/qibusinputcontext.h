#ifndef __Q_IBUS_INPUT_CONTEXT_H_
#define __Q_IBUS_INPUT_CONTEXT_H_

#include "qibusobject.h"
#include "qibusbus.h"

class InputContextAdaptor;

namespace IBus {

class InputContext;
typedef Pointer<InputContext> InputContextPointer;

class InputContext : public Object
{
    Q_OBJECT;

protected:

public:
    InputContext (void);
    ~InputContext (void);

public:
    static InputContextPointer create (const BusPointer &bus);

private:

/*
signals:
    void disconnected (void);
    void connected (void);

private slots:
    void slotAddressChanged (const QString &path);
    void slotIBusDisconnected (void);
*/
private:
};

};

#endif
