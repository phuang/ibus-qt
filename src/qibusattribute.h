#ifndef __Q_IBUS_ATTRIBUTE_H_
#define __Q_IBUS_ATTRIBUTE_H_

#include "qibusserializable.h"

namespace IBus {

class Attribute : public Serializable
{
    Q_OBJECT;

protected:

public:
    Attribute () {}
    Attribute (const QString &text) : m_text (text) {}

public:
    virtual bool serialize (QDBusArgument &argument) const;
    virtual bool deserialize (const QDBusArgument &argument);

private:
    QString m_text;

    IBUS_SERIALIZABLE
};

};

#endif
