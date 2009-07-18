#ifndef __Q_IBUS_PROP_LIST_H_
#define __Q_IBUS_PROP_LIST_H_

#include "qibusserializable.h"
#include "qibusproperty.h"

namespace IBus {

class PropList;
typedef Pointer<PropList> PropListPointer;

class PropList : public Serializable
{
    Q_OBJECT;

protected:

public:
    PropList (void);

public:
    virtual bool serialize (QDBusArgument &argument) const;
    virtual bool deserialize (const QDBusArgument &argument);

private:
    QList<PropertyPointer> m_props;

    IBUS_SERIALIZABLE
};

};

#endif
