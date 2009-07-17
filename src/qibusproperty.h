#ifndef __Q_IBUS_PROPERTY_H_
#define __Q_IBUS_PROPERTY_H_

#include "qibusserializable.h"

namespace IBus {

class Property;
typedef Pointer<Property> PropertyPointer;

class Property : public Serializable
{
    Q_OBJECT;

protected:

public:
    Property (void);
    Property (const QString &text) : m_text (text) {}

public:
    virtual bool serialize (QDBusArgument &argument) const;
    virtual bool deserialize (const QDBusArgument &argument);

private:
    QString m_text;

    IBUS_SERIALIZABLE
};

};

#endif
