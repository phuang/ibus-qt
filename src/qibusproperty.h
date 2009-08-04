#ifndef __Q_IBUS_PROPERTY_H_
#define __Q_IBUS_PROPERTY_H_

#include "qibusserializable.h"
#include "qibusproplist.h"
#include "qibustext.h"

namespace IBus {

class Property;
class PropList;
typedef Pointer<PropList> PropListPointer;
typedef Pointer<Property> PropertyPointer;

class Property : public Serializable
{
    Q_OBJECT;

/* type of QIBusProperty */
typedef enum
{
    TypeNormal = 0,
    TypeToggle = 1,
    TypeRadio = 2,
    TypeMenu = 3,
    TypeSeparator = 4,
}PropType;

/*
 * State of QIBusProperty. The actual effect
 * depends on #QIBusPropType of the QIBusProperty.
 */
typedef enum
{
    StateUnchecked = 0,
    StateChecked = 1,
    StateInconsistent = 2,
}PropState;

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
    void setSubProps (const PropListPointer & props);
    bool update (const PropertyPointer prop);

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
