#ifndef __Q_IBUS_COMPONENT_H_
#define __Q_IBUS_COMPONENT_H_

#include <QtXml/QDomNode>
#include "qibusserializable.h"

namespace IBus {

class Component;
typedef Pointer<Component> ComponentPointer;
typedef Pointer<QDomNode> QDomNodePointer;

class Component : public Serializable
{
    Q_OBJECT;

public:
    Component () {}
    Component (QString name,
               QString desc,
               QString vers,
               QString lics,
               QString auth,
               QString hmpg,
               QString exec,
               QString textdomain,
               QDomNode * engineNode,
               QDomNode * observedPathNode):
               m_name(name),
               m_description(desc),
               m_version(vers),
               m_license(lics),
               m_author(auth),
               m_homepage(hmpg),
               m_exec(exec),
               m_textdomain(textdomain),
               m_observedPathNode(observedPathNode),
               m_engineNode(engineNode)
    {}

    virtual ~Component ()
    {}

public:
    virtual bool serialize (QDBusArgument &argument) const;
    virtual bool deserialize (const QDBusArgument &argument);

private:
    QString m_name;
    QString m_description;
    QString m_version;
    QString m_license;
    QString m_author;
    QString m_homepage;
    QString m_exec;
    QString m_textdomain;

    // QVector<QDomNode *> m_observedPathNode;
    QDomNode * m_observedPathNode;
    QDomNode * m_engineNode;

    uint    m_pid;

    IBUS_SERIALIZABLE
};

};

#endif
