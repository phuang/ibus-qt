#ifndef __Q_IBUS_TEXT_H_
#define __Q_IBUS_TEXT_H_

#include "qibusserializable.h"

namespace IBus {

class Text : public Serializable
{
    Q_OBJECT;

protected:

public:
    Text ();

public:
    virtual bool serialize (QDBusArgument &argument) const;
    virtual bool deserialize (const QDBusArgument &argument);

    IBUS_SERIALIZABLE
};

};

#endif
