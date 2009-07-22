#ifndef __Q_IBUS_TEXT_H_
#define __Q_IBUS_TEXT_H_

#include "qibusserializable.h"
#include "qibusattribute.h"
#include "qibusattrlist.h"

namespace IBus {

class Text;
typedef Pointer<Text> TextPointer;

class Text : public Serializable
{
    Q_OBJECT;

protected:

public:
    Text () {}
    Text (const QString &text) : m_text (text) {}

public:
    virtual bool serialize (QDBusArgument &argument) const;
    virtual bool deserialize (const QDBusArgument &argument);

    const QString &text (void) { return m_text; }
    const AttrListPointer &attrs (void) { return m_attrs; }

private:
    QString m_text;
    AttrListPointer m_attrs;

    IBUS_SERIALIZABLE
};

};

#endif
