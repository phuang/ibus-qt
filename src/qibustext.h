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
    Text (const QString &text) : m_text (text), m_attrs(0) {}
    Text (const QChar &ch) : m_text (ch), m_attrs(0) {}

public:
    virtual bool serialize (QDBusArgument &argument);
    virtual bool deserialize (const QDBusArgument &argument);

    const QString &text (void) const            { return m_text; }
    const AttrListPointer &attrs (void) const   { return m_attrs; }
    const uint getLength (void) const           { return m_text.length(); }
    void appendAttribute (uint type, uint value, uint startIndex, int endIndex);

private:
    QString m_text;
    AttrListPointer m_attrs;

    IBUS_SERIALIZABLE
};

};

#endif
