#ifndef __Q_IBUS_PROPERTY_H_
#define __Q_IBUS_PROPERTY_H_

#include "qibusserializable.h"
#include "qibusproplist.h"
#include "qibustext.h"

namespace IBus {

class Property;
typedef Pointer<Property> PropertyPointer;

class Property : public Serializable
{
    Q_OBJECT;

/* type of QIBusProperty */
typedef enum
{
    PROP_TYPE_NORMAL = 0,
    PROP_TYPE_TOGGLE = 1,
    PROP_TYPE_RADIO = 2,
    PROP_TYPE_MENU = 3,
    PROP_TYPE_SEPARATOR = 4,
}IBusPropType;

/*
 * State of IBusProperty. The actual effect
 * depends on #IBusPropType of the IBusProperty.
 */
typedef enum
{
    PROP_STATE_UNCHECKED = 0,
    PROP_STATE_CHECKED = 1,
    PROP_STATE_INCONSISTENT = 2,
}IBusPropState;

public:
    Property () {}
    Property (const QString key,
              const QString icon,
              TextPointer label,
              TextPointer tooltip,
              bool sensitive,
              bool visible,
              uint type,
              uint state)
    : m_key(key),
      m_icon(icon),
      m_label(label),
      m_tooltip(tooltip),
      m_sensitive(sensitive),
      m_visible(visible),
      m_type(type),
      m_state(state)
    {}

    ~Property ()
    {}

public:
    virtual bool serialize (QDBusArgument &argument) const;
    virtual bool deserialize (const QDBusArgument &argument);

public:
    void setLabel (const TextPointer & lable);
    void setVisible (bool visible);
    void setSubProps (const PropListPointer & subProps);
    bool update (const Property & propUpdate);

private:

    QString m_key;
    QString m_icon;
    TextPointer m_label;
    TextPointer m_tooltip;
    bool m_sensitive;
    bool m_visible;
    uint m_type;
    uint m_state;

    PropListPointer m_subProps;

    IBUS_SERIALIZABLE
};

};

#endif
