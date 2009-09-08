#ifndef __Q_IBUS_ATTRLIST_H_
#define __Q_IBUS_ATTRLIST_H_

#include "qibusattribute.h"
#include <QVector>

namespace IBus {

class AttrList;
typedef Pointer<AttrList> AttrListPointer;

class AttrList : public Serializable {
    Q_OBJECT
public :
    AttrList (): m_attrs (0) {}
    virtual ~AttrList ();

public :
    AttributePointer get(int index) const;
    void append (const AttributePointer &attr);
    void clear (void);
    uint size (void) const { return m_attrs.size (); }

    AttributePointer operator[] (int index) const { return get (index); }

    virtual bool serialize (QDBusArgument &argument);
    virtual bool deserialize (const QDBusArgument &argument);

private :
    QVector<AttributePointer> m_attrs;

    IBUS_SERIALIZABLE
};

} /* IBUS */

#endif
