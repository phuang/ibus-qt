#include <stdio.h>
#include <QXmlStreamWriter>
#include "qibuscomponent.h"
#include "qibusobservedpath.h"
#include "qibusxml.h"

namespace IBus {

IBUS_DECLARE_SERIALIZABLE(Component, IBusComponent);

// this is a friend function, which is defined in class ObservedPath
const ObservedPathPointer newObserverdPathFromXmlNode (const QDomNode & node);

bool
Component::serialize (QDBusArgument &argument) const
{
    if (!Serializable::serialize (argument))
        return false;

    argument << m_name;
    argument << m_description;
    argument << m_version;
    argument << m_license;
    argument << m_author;
    argument << m_homepage;
    argument << m_exec;
    argument << m_textdomain;

    argument.beginArray(QDBusArgument::VariantType);
    for ( int i = 0; i < m_observedPaths.size(); ++i ) {
        argument << m_observedPaths[i];
    }
    argument.endArray();

    argument.beginArray(QDBusArgument::VariantType);
    for ( int i = 0; i < m_engines.size(); ++i ) {
        argument << m_engines[i];
    }
    argument.endArray();

    return true;
}

bool
Component::deserialize (const QDBusArgument &argument)
{
    if (!Serializable::deserialize (argument))
        return false;

    argument >> m_name;
    argument >> m_description;
    argument >> m_version;
    argument >> m_license;
    argument >> m_author;
    argument >> m_homepage;
    argument >> m_exec;
    argument >> m_textdomain;

    argument.beginArray();
    while ( !argument.atEnd() ) {
        EngineDescPointer ep ;
        argument >> ep;
        m_observedPaths.append(ep);
    }
    argument.endArray();

    argument.beginArray();
    while ( !argument.atEnd() ) {
        EngineDescPointer ep ;
        argument >> ep;
        m_engines.append(ep);
    }
    argument.endArray();

    return true;
}

void
Component::output (QString & output) const
{
    QXmlStreamWriter stream(&output);
    stream.setAutoFormatting(true);

    stream.writeStartElement("component");

    stream.writeTextElement("name", m_name); stream.writeTextElement("description", m_description);
    stream.writeTextElement("version", m_version);
    stream.writeTextElement("license", m_license);
    stream.writeTextElement("author", m_author);
    stream.writeTextElement("homepage", m_homepage);
    stream.writeTextElement("exec", m_exec);
    stream.writeTextElement("textdomain", m_textdomain);

    // for observed-paths
    stream.writeStartElement("observed-paths");
    for ( int i = 0; i < m_observedPaths.size(); ++i ) {
        stream.writeStartElement("path");

        QString mtime;
        mtime.number(m_observedPaths[i]->getMTime());
        stream.writeAttribute("mtime", mtime);
        stream.writeCharacters(m_observedPaths[i]->getPath());

        stream.writeEndElement();
    }
    stream.writeEndElement();

    // for engines
    stream.writeStartElement("engines");
    for ( int i = 0; i < m_engines.size(); ++i ) {
        // for one specfic engine
        stream.writeStartElement("engine");
        QMap<QString, QString> engineInfo = m_engines[i]->getEngineInfo();
        QMap<QString, QString>::const_iterator cIter = engineInfo.begin();
        for ( ; cIter != engineInfo.end(); ++cIter ) {
            stream.writeTextElement(cIter.key(), cIter.value());
        }
        stream.writeEndElement();
    }
    stream.writeEndElement();
    
    stream.writeEndElement();
}

bool
Component::parseXmlNode (const QDomNode & node)
{
    if ( node.nodeName().compare("component") )
        return false;

    QDomNode child = node.firstChild();
    for ( ; !child.isNull(); child = child.nextSibling() ) {
        if ( !child.nodeName().compare("name") ) {
            m_name = child.nodeValue();
        }
        else if ( !child.nodeName().compare("description") ) {
            m_description = child.nodeValue();
        }
        else if ( !child.nodeName().compare("version") ) {
            m_version = child.nodeValue();
        }
        else if ( !child.nodeName().compare("license") ) {
            m_license = child.nodeValue();
        }
        else if ( !child.nodeName().compare("author") ) {
            m_author = child.nodeValue();
        }
        else if ( !child.nodeName().compare("homepage") ) {
            m_homepage = child.nodeValue();
        }
        else if ( !child.nodeName().compare("exec") ) {
            m_exec = child.nodeValue();
        }
        else if ( !child.nodeName().compare("textdomain") ) {
            m_textdomain = child.nodeValue();
        }
        else if ( !child.nodeName().compare("observed-paths") ) {
            if ( !parseObservedPaths(child) ) {
                return false;
            }
        }
        else if ( !child.nodeName().compare("engines") ) {
            if ( !parseEngines(child) ) {
                return false;
            }
        }
        else {
            fprintf(stderr, "<component> element contains invalidate element %s\n", child.nodeName().data());
            return false;
        }
    }

    return true;
}

bool Component::parseObservedPaths(const QDomNode & node)
{
    if( node.nodeName().compare("observed-path") ) {
        return false;
    }

    int i = 0;
    QDomNode child = node.firstChild();
    for ( ; !child.isNull(); child = child.nextSibling(), ++i ) {
        // if ( !(m_observedPaths[i]->newObserverdPathFromXmlNode(child)) ) {
        if ( !(newObserverdPathFromXmlNode(child)) ) {
            return false;
        }
    }

    return true;
}

bool Component::parseEngines(const QDomNode & node)
{
    if ( node.nodeName().compare("engines") ) {
        return false;
    }

    int i = 0;
    QDomNode child = node.firstChild();
    for ( ; !child.isNull(); child = child.nextSibling(), ++i ) {
        if ( !(m_engines[i]->newEngineFromXmlNode(child)) ) {
            return false;
        }
    }

    return true;
}

const ComponentPointer Component::newComponentFromXmlNode (const QDomNode & root) const
{
    ComponentPointer compnt = new Component;
    if ( !compnt->parseXmlNode(root) ) {
        fprintf(stderr, "Component::newComponentFromXmlNode error!\n");
        return NULL;
    }

    return compnt;
}

const ComponentPointer Component::newComponentFromFile (const QString & filename) const
{
    const QDomNode * root = parseXmlFile(filename);
    if ( !root ) {
        return NULL;
    }

    return newComponentFromXmlNode(*root);
}

const QDomNode * Component::parseXmlFile (const QString & filename) const
{
    // need to code
    return NULL;
}

};
