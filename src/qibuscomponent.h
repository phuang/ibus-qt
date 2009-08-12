#ifndef __Q_IBUS_COMPONENT_H_
#define __Q_IBUS_COMPONENT_H_

#include <QFile>
#include <QDebug>
#include <QVector>
#include <QProcess>
#include <QXmlStreamWriter>
#include <QtXml/QDomNode>
#include "qibusserializable.h"
#include "qibusenginedesc.h"
#include "qibusobservedpath.h"

namespace IBus {

class Component;
typedef Pointer<Component> ComponentPointer;

class Component : public Serializable
{
    Q_OBJECT;

public:
    Component () {}
    Component (const QString & name,
               const QString & desc,
               const QString & vers,
               const QString & lics,
               const QString & auth,
               const QString & hmpg,
               const QString & exec,
               const QString & textdomain
               ):
               m_name(name),
               m_description(desc),
               m_version(vers),
               m_license(lics),
               m_author(auth),
               m_homepage(hmpg),
               m_exec(exec),
               m_textdomain(textdomain)
    {}

    virtual ~Component ()
    {}

public:
    virtual bool serialize (QDBusArgument &argument) const;
    virtual bool deserialize (const QDBusArgument &argument);

    void output (QString & output) const;
    bool parseXmlNode (const QDomNode & node);
    bool parseEngines (QDomNode node);
    bool parseObservedPaths (const QDomNode & node);

    void addObservedPath (const QString & filename);
    void addEngine (const EngineDescPointer edp);
    const ComponentPointer newComponentFromFile (const QString & filename) const;

    QVector<ObservedPathPointer> getObservedPathVec () const;
    const QVector<EngineDescPointer> & getEnginesVec () const;

    bool start (bool verbose) const;
    bool stop () const;
    bool isRunning () const;
    bool isComponentModified () const;
    const ComponentPointer getComponentFromEngine (EngineDescPointer edp) const;

private:
    const QDomDocument * parseXmlFile (const QString & filename) const;

private:
    QString m_name;
    QString m_description;
    QString m_version;
    QString m_license;
    QString m_author;
    QString m_homepage;
    QString m_exec;
    QString m_textdomain;

    QVector<ObservedPathPointer>    m_observedPaths;
    QVector<EngineDescPointer>      m_engines;

    uint    m_pid;

    IBUS_SERIALIZABLE
};

};

#endif
