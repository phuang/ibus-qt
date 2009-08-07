#include "qibuscomponent.h"

namespace IBus {

IBUS_DECLARE_SERIALIZABLE(Component, IBusComponent);

bool
Component::serialize (QDBusArgument &argument) const
{
    if (!Serializable::serialize (argument))
        return false;

    argument << m_name;
    argument << m_description;
    argument << m_version;
    argument << m_license;
    argument << m_author;
    argument << m_homepage;
    argument << m_exec;
    argument << m_textdomain;

    QDomNode * observedPathNode = m_observedPathNode;
    for ( ; observedPathNode != NULL; observedPathNode = &(observedPathNode->nextSibling()) ) {
        argument << observedPathNode;
    }
    // argument << m_observedPathNode;
    // argument << m_engineNode;

    return true;
}

bool
Component::deserialize (const QDBusArgument &argument)
{
    if (!Serializable::deserialize (argument))
        return false;

    argument >> m_name;
    argument >> m_description;
    argument >> m_version;
    argument >> m_license;
    argument >> m_author;
    argument >> m_homepage;
    argument >> m_exec;
    argument >> m_textdomain;

    // argument >> m_observedPathNode;
    // argument >> m_engineNode;

    return true;
}

};
