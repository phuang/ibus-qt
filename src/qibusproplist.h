#ifndef __Q_IBUS_PROP_LIST_H_
#define __Q_IBUS_PROP_LIST_H_

#include "qibusserializable.h"

namespace IBus {

class PropList;
typedef Pointer<PropList> PropListPointer;

class PropList : public Serializable
{
    Q_OBJECT;

protected:

public:
    PropList (void);
    PropList (const QString &text) : m_text (text) {}

public:
    virtual bool serialize (QDBusArgument &argument) const;
    virtual bool deserialize (const QDBusArgument &argument);

private:
    QString m_text;

    IBUS_SERIALIZABLE
};

};

#endif
