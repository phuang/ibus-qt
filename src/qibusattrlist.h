#ifndef __Q_IBUS_ATTRLIST_H_
#define __Q_IBUS_ATTRLIST_H_

#include "qibusattribute.h"
#include "QVector"

namespace IBUS {

class Attrlist {
    Q_OBJECT;
public:
    Attrlist (int size): m_attrlist(size){};
    virtual ~Attrlist ();
    Attribute * get(QVector<Attribute> *attrlist, uint index);
    void append(QVector<Attribute> *attrlist, Attribute *attr);

    virtual bool serialize( QVector<Attribute> *attrlist, )
private:
    QVector<Attribute> m_attrlist;

    IBUS_SERIALIZABLE
};

} /* IBUS */


#endif
