#ifndef __Q_IBUS_PROP_LIST_H_
#define __Q_IBUS_PROP_LIST_H_

#include "qibusserializable.h"
#include "qibustext.h"

namespace IBus {

class Property;
class PropList;
typedef Pointer<PropList> PropListPointer;

class PropList: public Serializable
{
    Q_OBJECT;

public:
    PropList ()
    {}
    PropList (const QVector<Property *> & props): m_props(props)
    {}

    virtual ~PropList ();

public:
    virtual bool serialize (QDBusArgument &argument) const;
    virtual bool deserialize (const QDBusArgument &argument);

    bool updateProperty (const Property & propUpdate);

private:
    QVector<Property *> m_props;
    // QVector<PropertyPointer> m_props;

    IBUS_SERIALIZABLE
};

};

#endif
