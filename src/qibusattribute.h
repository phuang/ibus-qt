#ifndef __Q_IBUS_ATTRIBUTE_H_
#define __Q_IBUS_ATTRIBUTE_H_

#include "qibusserializable.h"

namespace IBus {

typedef enum {
    IBUS_ATTR_TYPE_UNDERLINE  =1,
    IBUS_ATTR_TYPE_FOREGROUND =2,
    IBUS_ATTR_TYPE_BACKGROUND =3,
} IBusAttrType;    

class Attribute;
typedef Pointer<Attribute> AttributePointer;

class Attribute : public Serializable
{
    Q_OBJECT;


public:
    Attribute (uint type = 0, uint value = 0, uint start = 0, uint end = 0) :
    m_type (type), m_value (value),m_start_index (start), m_end_index (end) {}


public:
    virtual bool serialize (QDBusArgument &argument) const;
    virtual bool deserialize (const QDBusArgument &argument);

protected:
    uint m_type;
    uint m_value;
    uint m_start_index;
    uint m_end_index;

    IBUS_SERIALIZABLE
};

class AttributeUnderline : public Attribute 
{
    Q_OBJECT;


public:
    AttributeUnderline (uint type= 0, uint start = 0, uint end = 0) { 
        m_type          = IBUS_ATTR_TYPE_UNDERLINE;
        m_value         = type;
        m_start_index   = start;
        m_end_index     = end;
    }


    IBUS_SERIALIZABLE
};

class AttributeForeground: public Attribute 
{
    Q_OBJECT;


public:
    AttributeUnderline (uint color= 0, uint start = 0, uint end = 0) { 
        m_type          = IBUS_ATTR_TYPE_FOREGROUND;
        m_value         = color;
        m_start_index   = start;
        m_end_index     = end;
    }


    IBUS_SERIALIZABLE
};

class AttributeBackground: public Attribute 
{
    Q_OBJECT;


public:
    AttributeUnderline (uint color= 0, uint start = 0, uint end = 0) { 
        m_type          = IBUS_ATTR_TYPE_BACKGROUND;
        m_value         = color;
        m_start_index   = start;
        m_end_index     = end;
    }


    IBUS_SERIALIZABLE
};

};

#endif
