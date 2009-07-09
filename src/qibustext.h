#ifndef __Q_IBUS_TEXT_H_
#define __Q_IBUS_TEXT_H_

#include "qibusserializable.h"

class QIBusText : public QIBusSerializable
{
protected:

public:
    QIBusText ();

public:
    virtual bool serialize (QDBusArgument &argument);
    virtual bool deserialize (QDBusArgument &argument);
    virtual QIBusText *copy ();

    IBUS_SERIALIZABLE
};

#endif
