#ifndef __Q_IBUS_ENGINE_DESC_H_
#define __Q_IBUS_ENGINE_DESC_H_

#include "qibusserializable.h"
#include "qibusxml.h"

namespace IBus {

class EngineDesc;
typedef Pointer<EngineDesc> EngineDescPointer;

class EngineDesc : public Serializable
{
    Q_OBJECT;

public:
    EngineDesc (): m_rank(0) {}
    EngineDesc (QString name,
                QString lname,
                QString desc,
                QString lang,
                QString lics,
                QString auth,
                QString icon,
                QString layout):
                m_name(name),
                m_longname(lname),
                m_description(desc),
                m_language(lang),
                m_license(lics),
                m_author(auth),
                m_icon(icon),
                m_layout(layout) {}

    virtual ~EngineDesc() {}

public:
    virtual bool serialize (QDBusArgument &argument) const;
    virtual bool deserialize (const QDBusArgument &argument);

    void output (QString & output) const;
    void output (QString & output, const uint indent) const;
    bool parseXmlNode (const XMLNode * node);

private:
    inline void appendIndent (QString & str, const uint indent) const
    {
        for ( uint i = 0; i < indent; ++i ) {
            str.append("    ");
        }
    }

    inline void outputEntry(QString & buf, const QString & name, const QString & value, const uint indent) const
    {
        appendIndent(buf, indent);
        QString entry = "<" + name + ">" + value + "</" + name + ">\n";
        buf += entry;
    }

    inline void parseEntry(const XMLNode & node, const QString & name, QString & text)
    {
        if ( !name.compare(node.name) )
            text = node.text;
    }

private:
    QString m_name;
    QString m_longname;
    QString m_description;
    QString m_language;
    QString m_license;
    QString m_author;
    QString m_icon;
    QString m_layout;
    uint    m_rank;

    IBUS_SERIALIZABLE
};

};

#endif
