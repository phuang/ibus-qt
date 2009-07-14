#ifndef __Q_IBUS_TEXT_H_
#define __Q_IBUS_TEXT_H_

#include "qibusserializable.h"

namespace IBus {

class Text : public Serializable
{
protected:

public:
    Text ();

public:
    virtual bool serialize (QDBusArgument &argument);
    virtual bool deserialize (QDBusArgument &argument);
    virtual Text *copy ();

    IBUS_SERIALIZABLE
};

};

#endif
