#include "qibusobservedpath.h"

namespace IBus {

IBUS_DECLARE_SERIALIZABLE(ObservedPath, IBusObservedPath);

bool
ObservedPath::serialize (QDBusArgument & argument) const
{
    if ( !Serializable::serialize(argument) ) {
        return false;
    }

    argument << m_path;
    argument << m_mtime;

    return true;
}

bool
ObservedPath::deserialize (const QDBusArgument & argument)
{
    if ( !Serializable::deserialize(argument) ) {
        return false;
    }

    argument >> m_path;
    argument >> m_mtime;

    return true;
}

bool
ObservedPath::parseXmlNode (const QDomNode & node)
{
    if ( node.nodeName().compare("path") ) {
        return false;
    }

    // process path
    int lstIdx = node.nodeValue().lastIndexOf('/');
    QDir path(node.nodeValue().left(lstIdx));

    if ( !path.isReadable() ) {
        return false;
    }

    if ( path.isAbsolute() ) {
        m_path = node.nodeValue();
    }
    else if ( path.isRelative() ) {
        if ( node.nodeValue()[0] == '~' ) {
            QString homePath = QDir::homePath();
            m_path += homePath;
            m_path += node.nodeValue().right(node.nodeValue().size() - 2);
        }
        else if ( node.nodeValue()[0] == '.' && node.nodeValue()[1] == '/' ) {
            QString curPath = QDir::currentPath();
            m_path += curPath;
            m_path += node.nodeValue().right(node.nodeValue().size() - 2);
        }
        else {
            QString curPath = QDir::currentPath();
            m_path += curPath;
            m_path += node.nodeValue();
        }
    }
    else {
        fprintf(stderr, "Invalid path: %s\n", node.nodeValue().data());
        return false;
    }

    // process mtime
    if ( node.hasAttributes() ) {
        QDomNamedNodeMap nnMap = node.attributes();
        for ( uint i = 0; i < nnMap.length(); ++i ) {
            QDomNode attrNode = nnMap.item(i);
            if ( !attrNode.nodeName().compare("mtime") ) {
                m_mtime = attrNode.nodeValue().toInt();
            }
        }
    }

    return true;
}

bool
ObservedPath::isObservedPathModified () const
{
    QFileInfo fi(m_path);
    if ( m_mtime == fi.lastModified().toTime_t() ) {
       return false;
    }

    return true;
}

void
ObservedPath::setObservedPathStat ()
{
    QFileInfo fi(m_path);
    if ( fi.exists() ) {
        m_isExist = true;
        m_mtime = fi.lastModified().toTime_t();
        if ( fi.isDir() ) {
            m_isDir = true;
        }
    }
    else {
        m_isExist = false;
        m_isDir = false;
        m_mtime = 0;
    }
}

void
ObservedPath::traverseObservedPath (QVector<ObservedPathPointer> & observedPathVec) const
{
    QDir dir(m_path);
    QStringList files = dir.entryList();

    for ( int i = 0; i < files.size(); ++i ) {
        QString file = files.at(i);
        ObservedPathPointer observedPathPtr = new ObservedPath(file);
        observedPathPtr->setObservedPathStat();

        if ( observedPathPtr->isRegularFile() ) {
            observedPathVec.push_back(observedPathPtr);
        }
        else if ( observedPathPtr->isDirFile() ) {
            observedPathPtr->traverseObservedPath(observedPathVec);
        }
    }
}

};
