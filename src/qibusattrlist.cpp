#include "qibusattrlist.h"

namespace IBus {

IBUS_DECLARE_SERIALIZABLE(AttrList, IBusAttrList);

AttrList::~AttrList ()
{
    m_attrs.clear();
}

AttributePointer AttrList::get (uint index)
{
    if (index >= m_attrs.size ())
        return NULL;
    return m_attrs[index];
}

void AttrList::append(const AttributePointer &attr)
{
    if (attr.isNull ())
        return;

    m_attrs.append (attr);
}

bool AttrList::serialize (QDBusArgument &argument) const
{
    argument.beginArray (QDBusArgument::VariantType);
    for (int i = 0; i < m_attrs.size(); i++) {
        argument << (SerializablePointer) m_attrs[i];
    }
    argument.endArray ();
    return true;
}

bool AttrList::deserialize (const QDBusArgument &argument)
{
    argument.beginArray ();
    while (!argument.atEnd ()) {
        SerializablePointer attr;
        argument >> attr;
        append (attr);
    }
    argument.endArray ();
    return true;
}

} /* IBus */
