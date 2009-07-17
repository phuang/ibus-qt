#ifndef __Q_IBUS_COMPONENT_H_
#define __Q_IBUS_COMPONENT_H_

#include "qibusserializable.h"

namespace IBus {

class Component;
typedef Pointer<Component> ComponentPointer;

class Component : public Serializable
{
    Q_OBJECT;

protected:

public:
    Component (void);
    Component (const QString &text) : m_text (text) {}

public:
    virtual bool serialize (QDBusArgument &argument) const;
    virtual bool deserialize (const QDBusArgument &argument);

private:
    QString m_text;

    IBUS_SERIALIZABLE
};

};

#endif
