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
    if ( m_attrs.isNull () ) {
        m_attrs = new AttrList ();
    }

    argument << qDBusVariantFromSerializable(m_attrs);
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

void
Text::appendAttribute (uint type, uint value, uint startIndex, int endIndex)
{
    if ( endIndex < 0 ) {
        endIndex += getLength() + 1;
    }

    if ( endIndex <= 0 ) {
        return ;
    }

    if ( m_attrs.isNull() ) {
        m_attrs = new AttrList();
    }

    AttributePointer attribute = new Attribute (type, value, startIndex, endIndex);
    m_attrs->append(attribute);
}

};
