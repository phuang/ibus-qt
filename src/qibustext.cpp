#include <QDebug>
#include "qibustext.h"

namespace IBus {

IBUS_DECLARE_SERIALIZABLE(Text, IBusText);

bool
Text::serialize (QDBusArgument &argument)
{
    if (!Serializable::serialize (argument))
        return false;
    argument << m_text;
    if (m_attrs.isNull ())
        m_attrs = new AttrList ();
    argument << m_attrs;
    return true;
}

bool
Text::deserialize (const QDBusArgument &argument)
{
    if (!Serializable::deserialize (argument))
        return false;
    argument >> m_text;
    argument >> m_attrs;
    return true;
}

};
