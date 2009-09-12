#ifndef __Q_IBUS_ATTRIBUTE_H_
#define __Q_IBUS_ATTRIBUTE_H_

#include "qibusserializable.h"

namespace IBus {

class Attribute;
typedef Pointer<Attribute> AttributePointer;


class Attribute : public Serializable
{
    Q_OBJECT

public:
    /*
     * Type enumeration of IBusText attribute.
     */
    typedef enum {
        TypeUnderline  = 1,
        TypeForeground = 2,
        TypeBackground = 3,
    } Type;
    
    /*
     * Type of IBusText attribute.
     */
    typedef enum {
        UnderlineNone   = 0,
        UnderlineSingle = 1,
        UnderlineDouble = 2,
        UnderlineLow    = 3,
        UnderlineError  = 4,
    } Underline;

public:
    Attribute (uint type = 0, uint value = 0, uint start = 0, uint end = 0) :
    m_type (type), m_value (value),m_start (start), m_end (end) {}

public:
    virtual bool serialize (QDBusArgument &argument);
    virtual bool deserialize (const QDBusArgument &argument);

    uint type (void) const { return m_type; }
    uint value (void) const { return m_value; }
    uint start (void) const { return m_start; }
    uint end (void) const { return m_end; }
    uint length (void) const { return (m_end - m_start); }

protected:
    uint    m_type;
    uint    m_value;
    uint    m_start;
    uint    m_end;

    IBUS_SERIALIZABLE
};

class AttributeUnderline : public Attribute
{
public:
    AttributeUnderline (uint underlineType = 0, uint start = 0, uint end = 0)
        : Attribute (TypeUnderline, underlineType, start, end) {}
};

class AttributeForeground: public Attribute
{
public:
    AttributeForeground (uint color = 0, uint start = 0, uint end = 0)
        : Attribute (TypeForeground, color, start, end) {}
};

class AttributeBackground: public Attribute
{
public:
    AttributeBackground (uint color = 0, uint start = 0, uint end = 0)
        : Attribute (TypeBackground, color, start, end) {}
};

};

#endif
