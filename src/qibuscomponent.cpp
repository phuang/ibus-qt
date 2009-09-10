#include "qibuscomponent.h"

namespace IBus {

IBUS_DECLARE_SERIALIZABLE(Component, IBusComponent);

bool
Component::serialize (QDBusArgument &argument)
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

    argument.beginArray(qMetaTypeId<QDBusVariant>());
    for ( int i = 0; i < m_observedPaths.size(); ++i ) {
        argument << m_observedPaths[i];
    }
    argument.endArray();

    argument.beginArray(qMetaTypeId<QDBusVariant>());
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

    stream.writeTextElement("name", m_name);
    stream.writeTextElement("description", m_description);
    stream.writeTextElement("version", m_version);
    stream.writeTextElement("license", m_license);
    stream.writeTextElement("author", m_author);
    stream.writeTextElement("homepage", m_homepage);
    stream.writeTextElement("exec", m_exec);
    stream.writeTextElement("textdomain", m_textdomain);

    // for observed-paths
    if ( m_observedPaths.size() > 0 ) {
        stream.writeStartElement("observed-paths");
        for ( int i = 0; i < m_observedPaths.size(); ++i ) {
            stream.writeStartElement("path");

            QString mtime;
            mtime.number(m_observedPaths[i]->mtime());
            stream.writeAttribute("mtime", mtime);
            stream.writeCharacters(m_observedPaths[i]->path());

            stream.writeEndElement();
        }
        stream.writeEndElement();
    }

    // for engines
    // stream.writeComment("for static engines");
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
    if ( node.isNull() || node.nodeName().compare("component") ) {
        return false;
    }

    bool errFlag = false;
    QDomNode child = node.firstChild();
    for ( ; !child.isNull(); child = child.nextSibling() ) {
        if ( !child.nodeName().compare("name") ) {
            m_name = child.toElement().text();
        }
        else if ( !child.nodeName().compare("description") ) {
            m_description = child.toElement().text();
        }
        else if ( !child.nodeName().compare("version") ) {
            m_version = child.toElement().text();
        }
        else if ( !child.nodeName().compare("license") ) {
            m_license = child.toElement().text();
        }
        else if ( !child.nodeName().compare("author") ) {
            m_author = child.toElement().text();
        }
        else if ( !child.nodeName().compare("homepage") ) {
            m_homepage = child.toElement().text();
        }
        else if ( !child.nodeName().compare("exec") ) {
            m_exec = child.toElement().text();
        }
        else if ( !child.nodeName().compare("textdomain") ) {
            m_textdomain = child.toElement().text();
        }
        /*
        else if ( !child.nodeName().compare("observed-paths") ) {
            if ( !parseObservedPaths(child) ) {
                return false;
            }
        }
        else if ( !child.nodeName().compare("engines") ) {
            if ( !parseEnginesNode(child) ) {
                return false;
            }
        }
        */
        else {
            QString s;
            QXmlStreamWriter stream(&s);
            stream.writeTextElement(child.nodeName(), child.toElement().text());
            qDebug() << "Component::parseXmlNode, Unknown element, " << s;

            // errFlag = true;
            continue;
        }
    }

    if ( !errFlag ) {
        return false;
    }

    return true;
}

#if 0

bool
Component::parseObservedPaths(const QDomNode & node)
{
    if( node.isNull() || node.nodeName().compare("observed-paths") ) {
        return false;
    }

    qDebug () << "Component::parseObservedPaths";

    int i = 0;
    QDomNode child = node.firstChild();
    for ( ; !child.isNull(); child = child.nextSibling(), ++i ) {
        ObservedPathPointer obsPath = new ObservedPath(child.toElement().text());
        addObservedPath(obsPath);

        if ( obsPath->isDirFile() ) {
            qDebug () << "It's dir file!";
            obsPath->traverseObservedPath(m_observedPaths);
        }
    }

    return true;
}


bool
Component::parseEnginesNode(QDomNode &node)
{
    if ( node.isNull() || node.nodeName().compare("engines") ) {
        return false;
    }

    QString exec;
    const QDomDocument * doc = NULL;

    if ( node.hasAttributes() ) {
        QDomNamedNodeMap nnMap = node.attributes();
        for ( uint i = 0; i < nnMap.length(); ++i ) {
            QDomNode attrNode = nnMap.item(i);
            if ( !attrNode.nodeName().compare("exec") ) {
                exec = attrNode.nodeValue();
            }
        }
    }

    if ( 0 != exec.size() ) {
        QProcess * newProc = new QProcess;
        newProc->start(exec);
        if ( newProc->waitForFinished(3000) ) {}
        QByteArray output = newProc->readAllStandardOutput();

        if ( output.isEmpty() ) {
            qDebug() << "Component::parseEnginesNode: " << "empty engines! invalid engines!!!";
            return false;
        }

        doc = parseXmlBuffer(output);
        const QDomNode enginesNode = static_cast<QDomNode>(doc->documentElement());
        if ( 0 == enginesNode.nodeName().compare("engines") ) {
            node = enginesNode;
        }

        delete newProc;
    }

    int i = 0;
    QDomNode child = node.firstChild();
    for ( ; !child.isNull(); child = child.nextSibling(), ++i ) {
        EngineDescPointer engDesc = new EngineDesc;
        if( !engDesc->parseXmlNode(child) ) {
            return false;
        }

        addEngine(engDesc);
    }

    if ( !doc ) {
        delete doc;
    }

    return true;
}

#endif

bool
newComponentFromFile (Component &obj, const QString & filename)
{
    const QDomDocument * doc = obj.parseXmlFile(filename);
    if ( !doc ) {
        return false;
    }

    QDomElement docElem = doc->documentElement();
    QDomNode root = static_cast<QDomNode>(docElem);

    if( obj.parseXmlNode(root) ) {
        qDebug() << "Component::newComponentFromFile: parseXmlNode error!";
        delete doc;
        return false;
    }

    // append filename to m_observedPath in obj
    ObservedPathPointer observedPathPtr = new ObservedPath(filename);
    if ( !observedPathPtr ) {
        qDebug() << "Component::newComponentFromFile: new error!";
        delete doc;
        return false;
    }
    // observedPathPtr->setObservedPathStat();
    obj.observedPaths().push_back(observedPathPtr);

    delete doc;
    return true;
}

const QDomDocument * 
Component::parseXmlFile (const QString & filename) const
{
    QFile file(filename);
    if ( !file.open(QIODevice::ReadOnly) ) {
        qDebug() << "Component::parseXmlFile: open \"" << filename << "\" failed!";
        return NULL;
    }

    QString errMsg;
    int errLine;
    int errColumn;

    QDomDocument * doc = new QDomDocument;
    if( !doc ) {
        qDebug() << "Component::parseXmlFile: " << "new error!";
        return NULL;
    }

    if ( !doc->setContent(&file, &errMsg, &errLine, &errColumn) ) {
        qDebug() << errMsg << "line: " << errLine <<", column: " << errColumn;
        return NULL;
    }

    file.close();
    return doc;
}

const QDomDocument * 
Component::parseXmlBuffer (const QByteArray & buf)
{
    QString errMsg;
    int errLine;
    int errColumn;

    QDomDocument * doc = new QDomDocument;
    if( !doc ) {
        qDebug() << "Component::parseXmlBuffer: " << "new error!";
        return NULL;
    }

    if ( !doc->setContent(buf, &errMsg, &errLine, &errColumn) ) {
        qDebug() << errMsg << "line: " << errLine <<", column: " << errColumn;
        return NULL;
    }

    return doc;
}

void
Component::addObservedPath (const ObservedPathPointer &obsPath)
{
    // obsPath->setObservedPathStat();
    m_observedPaths.push_back(obsPath);
}

void
Component::addEngine (const EngineDescPointer &edp)
{
    m_engines.push_back(edp);
}

QVector<ObservedPathPointer>
Component::observedPaths () const
{
    return m_observedPaths;
}

const QVector<EngineDescPointer> &
Component::engines () const
{
    return m_engines;
}

#if 0

bool
Component::start (bool verbose) const
{ return true; /* need to code */ }

bool
Component::stop () const
{ return true; /* need to code */ }

bool
Component::isRunning () const
{
    return (m_pid == 0);
}

bool
Component::isComponentModified () const
{
    for ( int i = 0; i < m_observedPaths.size(); ++i ) {
        if ( m_observedPaths[i]->isObservedPathModified() ) {
            return true;
        }
    }

    return false;
}

const ComponentPointer
Component::getComponentFromEngine (EngineDescPointer edp) const
{ /* need to code */ }

#endif

};
