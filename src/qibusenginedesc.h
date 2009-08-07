#ifndef __Q_IBUS_ENGINE_DESC_H_
#define __Q_IBUS_ENGINE_DESC_H_

#include <QtXml/QDomNode>
#include "qibusserializable.h"

namespace IBus {

class EngineDesc;
typedef Pointer<EngineDesc> EngineDescPointer;
typedef Pointer<QDomNode> QDomNodePointer;

class EngineDesc : public Serializable
{
    Q_OBJECT;

public:
    EngineDesc (): m_rank(0)
    {
        initialize();
    }
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
                m_layout(layout)
    {
        initialize();
    }

    virtual ~EngineDesc() {}

public:
    virtual bool serialize (QDBusArgument &argument) const;
    virtual bool deserialize (const QDBusArgument &argument);

    void output (QString & output) const;
    bool parseXmlNode (const QDomNodePointer node);


private:
    void initialize ()
    {
        m_memInEngine.insert("name", false);
        m_memInEngine.insert("longname", false);
        m_memInEngine.insert("description", false);
        m_memInEngine.insert("language", false);
        m_memInEngine.insert("license", false);
        m_memInEngine.insert("author", false);
        m_memInEngine.insert("icon", false);
        m_memInEngine.insert("layout", false);
        m_memInEngine.insert("rank", false);
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

    QMap<QString, bool> m_memInEngine;

    IBUS_SERIALIZABLE
};

};

#endif
