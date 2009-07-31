#include "qibusproperty.h"

namespace IBus {

IBUS_DECLARE_SERIALIZABLE(Property, IBusProperty);

Property::Property (void)
{
}

bool
Property::serialize (QDBusArgument &argument) const
{
    if (!Serializable::serialize (argument))
        return false;

    argument << m_key;
    argument << m_icon;
    argument << m_label;
    argument << m_tooltip;
    argument << m_sensitive;
    argument << m_visible;
    argument << m_type;
    argument << m_state;

    return true;
}

bool
Property::deserialize (const QDBusArgument &argument)
{
    if (!Serializable::deserialize (argument))
        return false;

    argument >> m_key;
    argument >> m_icon;
    argument >> m_label;
    argument >> m_tooltip;
    argument >> m_sensitive;
    argument >> m_visible;
    argument >> m_type;
    argument >> m_state;

    return true;
}

void
Property::setLabel (const TextPointer & lable)
{
    if ( !lable )
        return ;

    m_label = lable;
}

void
Property::setVisible (bool visible)
{
    m_visible = visible;
}



};
