#ifndef __Q_IBUS_ATTRIBUTE_H_
#define __Q_IBUS_ATTRIBUTE_H_

#include "qibusserializable.h"

namespace IBus {

class Attribute : public Serializable
{
    Q_OBJECT;

protected:

public:
    Attribute () {
	m_text ="";
	m_type =0;
	m_value =0;
	m_start_index =0;
	m_end_index =0;
	}
    Attribute (const QString &text) : m_text (text) {}

public:
    virtual bool serialize (QDBusArgument &argument) const;
    virtual bool deserialize (const QDBusArgument &argument);

private:
    QString m_text;
    uint m_type;
    uint m_value;
    uint m_start_index;
    uint m_end_index;

    IBUS_SERIALIZABLE
};

};

#endif
