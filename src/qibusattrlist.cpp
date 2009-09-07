#include "qibusattrlist.h"

namespace IBus {

IBUS_DECLARE_SERIALIZABLE(AttrList, IBusAttrList);

AttrList::~AttrList ()
{
    m_attrs.clear();
}

AttributePointer AttrList::get (int index) const
{
    if (index >= m_attrs.size ())
        return NULL;
    return m_attrs[index];
}

void AttrList::append (const AttributePointer &attr)
{
    if (attr.isNull ())
        return;

    m_attrs.append (attr);
}

void AttrList::clear (void)
{
    m_attrs.clear ();
}

bool AttrList::serialize (QDBusArgument &argument)
{
    if (!Serializable::serialize (argument)) {
        return false;
    }

    argument.beginArray (qMetaTypeId<QDBusVariant>());
    for (int i = 0; i < m_attrs.size(); i++) {
        argument << m_attrs[i];
    }
    argument.endArray ();

    return true;
}

bool AttrList::deserialize (const QDBusArgument &argument)
{
    clear ();

    if (!Serializable::deserialize (argument)) {
        return false;
    }

    argument.beginArray ();
    while (!argument.atEnd ()) {
        AttributePointer attr;
        argument >> attr;
        append (attr);
    }
    argument.endArray ();

    return true;
}

} /* IBus */
