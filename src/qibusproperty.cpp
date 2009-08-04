#include "qibusproperty.h"

namespace IBus {

IBUS_DECLARE_SERIALIZABLE(Property, IBusProperty);

bool
Property::serialize (QDBusArgument &argument) const
{
    if (!Serializable::serialize (argument)) {
        return false;
    }

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
    if (!Serializable::deserialize (argument)) {
        return false;
    }

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
    if ( !lable ) {
        m_label = new Text;
        return ;
    }

    m_label = lable;
}

void
Property::setVisible (bool visible)
{
    m_visible = visible;
}

void
Property::setSubProps(const PropListPointer & props)
{
    if ( !props ) {
        m_subProps = new PropList;
        return ;
    }

    m_subProps = props;
}

bool
Property::update (const PropertyPointer prop)
{
    if ( m_key == prop->m_key ) {
        m_icon = prop->m_icon;
        m_label = prop->m_label;
        m_tooltip = prop->m_tooltip;
        m_visible = prop->m_visible;
        m_sensitive = prop->m_sensitive;
        m_state = prop->m_state;

        return true;
    }

    if ( !m_subProps.isNull() )
        return m_subProps->updateProperty(prop);

    return false;
}

};
