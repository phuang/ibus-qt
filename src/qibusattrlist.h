#ifndef __Q_IBUS_ATTRLIST_H_
#define __Q_IBUS_ATTRLIST_H_

#include "qibusattribute.h"
#include <QVector>

namespace IBus {

class AttrList;
typedef Pointer<AttrList> AttrListPointer;

class AttrList : public Serializable {
    Q_OBJECT;
public:
    AttrList (): m_attrs (0) {}
    virtual ~AttrList ();
    AttributePointer get(uint index);
    void append (const AttributePointer &attr);
    void clear (void);

    virtual bool serialize (QDBusArgument &argument) const;
    virtual bool deserialize (const QDBusArgument &argument);
private:
    QVector<AttributePointer> m_attrs;

    IBUS_SERIALIZABLE
};

} /* IBUS */


#endif
