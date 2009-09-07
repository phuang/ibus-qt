#ifndef __Q_IBUS_PROP_LIST_H_
#define __Q_IBUS_PROP_LIST_H_

#include "qibusserializable.h"
#include "qibusproperty.h"
#include "qibustext.h"

namespace IBus {

class Property;
class PropList;
typedef Pointer<PropList> PropListPointer;
typedef Pointer<Property> PropertyPointer;

class PropList: public Serializable
{
    Q_OBJECT;

public:
    PropList () {}
    ~PropList () {}

public:
    virtual bool serialize (QDBusArgument &argument);
    virtual bool deserialize (const QDBusArgument &argument);

public :
    bool appendProperty (const PropertyPointer &prop);
    bool updateProperty (const PropertyPointer &prop);

private:
    QVector<PropertyPointer> m_props;

    IBUS_SERIALIZABLE
};

};

#endif
