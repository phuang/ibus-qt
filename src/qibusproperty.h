#ifndef __Q_IBUS_PROPERTY_H_
#define __Q_IBUS_PROPERTY_H_

#include "qibusserializable.h"
#include "qibustext.h"

namespace IBus {

class Property;
typedef Pointer<Property> PropertyPointer;

class Property : public Serializable
{
    Q_OBJECT;

protected:

public:
    Property (void);

public:
    virtual bool serialize (QDBusArgument &argument) const;
    virtual bool deserialize (const QDBusArgument &argument);

public:
    void setLabel(const TextPointer & lable);
    void setVisible(bool visible);

private:
    QString m_key;
    QString m_icon;
    TextPointer m_label;
    TextPointer m_tooltip;
    bool m_sensitive;
    bool m_visible;
    uint m_type;
    uint m_state;

    IBUS_SERIALIZABLE
};

};

#endif
