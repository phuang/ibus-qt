#include "qibusproperty.h"

namespace IBus {

IBUS_DECLARE_SERIALIZABLE(Property, IBusProperty);

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
    {
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
Property::setSubProps(const PropListPointer & subProps)
{
    if ( !subProps )
    {
        m_subProps = new PropList;
        return ;
    }

    m_subProps = subProps;
}

bool
Property::update (const Property & propUpdate)
{
    if ( m_key != propUpdate.m_key )
        return m_subProps->updateProperty(propUpdate);

    m_icon = propUpdate.m_icon;
    m_label = propUpdate.m_label;
    m_tooltip = propUpdate.m_tooltip;
    m_visible = propUpdate.m_visible;
    m_sensitive = propUpdate.m_sensitive;
    m_state = propUpdate.m_state;

    return true;
}

};
