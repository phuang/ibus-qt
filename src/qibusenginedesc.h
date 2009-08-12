#ifndef __Q_IBUS_ENGINE_DESC_H_
#define __Q_IBUS_ENGINE_DESC_H_

#include <QDebug>
#include <QXmlStreamWriter>
#include <QtXml/QDomNode>
#include "qibusserializable.h"

namespace IBus {

class EngineDesc;
typedef Pointer<EngineDesc> EngineDescPointer;

class EngineDesc : public Serializable
{
    Q_OBJECT;

public:
    EngineDesc (): m_rank(0)
    {}
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
    {}

    virtual ~EngineDesc() {}

public:
    virtual bool serialize (QDBusArgument &argument) const;
    virtual bool deserialize (const QDBusArgument &argument);

    void output (QString & output) const;
    bool parseXmlNode (const QDomNode & node);

    const QMap<QString, QString> & getEngineInfo() const
    {
        return m_engineInfo;
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

    QMap<QString, QString> m_engineInfo;

    IBUS_SERIALIZABLE
};

};

#endif
