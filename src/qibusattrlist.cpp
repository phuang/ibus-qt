#include "qibusattrlist.h"

namespace IBus {
Attribute* 
Attrlist::get(QVector<Attribute> *attrlist, uint index)
{
    if (*attrlist.size <index) {
    	return NULL;
    }
    return  &attrlist[index];

}

void
append( QVector<Attribute> *attrlist, Attribute *attr)
{
    *attrlist.append(*attr);
}


} /* IBus */
