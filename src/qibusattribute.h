#ifndef __Q_IBUS_ATTRIBUTE_H_
#define __Q_IBUS_ATTRIBUTE_H_

#include "qibusserializable.h"

namespace IBus {

class Attribute;
typedef Pointer<Attribute> AttributePointer;

class Attribute : public Serializable
{
    Q_OBJECT;

protected:

public:
    Attribute (uint type = 0, uint value = 0, uint start = 0, uint end = 0) :
    m_type (type), m_value (value),m_start_index (start), m_end_index (end) {}


public:
    virtual bool serialize (QDBusArgument &argument) const;
    virtual bool deserialize (const QDBusArgument &argument);

    void attribute_underline( uint type, uint start, uint end);
    void attribute_foreground( uint color, uint start, uint end);
    void attribute_background( uint color, uint start, uint end);

private:
    uint m_type;
    uint m_value;
    uint m_start_index;
    uint m_end_index;

    IBUS_SERIALIZABLE
};

};

#endif
