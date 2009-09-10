#include "qibusobservedpath.h"

namespace IBus {

IBUS_DECLARE_SERIALIZABLE(ObservedPath, IBusObservedPath);

bool
ObservedPath::serialize (QDBusArgument & argument)
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
    int lstIdx = node.toElement().text().lastIndexOf('/');
    QDir path(node.toElement().text().left(lstIdx));

    if ( !path.isReadable() ) {
        return false;
    }

    if ( path.isAbsolute() ) {
        m_path = node.toElement().text();
    }
    else if ( path.isRelative() ) {
        if ( node.toElement().text()[0] == '~' ) {
            QString homePath = QDir::homePath();
            m_path += homePath;
            m_path += node.toElement().text().right(node.toElement().text().size() - 2);
        }
        else if ( node.toElement().text()[0] == '.' && node.toElement().text()[1] == '/' ) {
            QString curPath = QDir::currentPath();
            m_path += curPath;
            m_path += node.toElement().text().right(node.toElement().text().size() - 2);
        }
        else {
            QString curPath = QDir::currentPath();
            m_path += curPath;
            m_path += node.toElement().text();
        }
    }
    else {
        qDebug() << "ObservedPath::parseXmlNode: invalid path! \"" << node.toElement().text() << "\"";
        return false;
    }

    // process mtime
    if ( node.hasAttributes() ) {
        QDomNamedNodeMap nnMap = node.attributes();
        for ( uint i = 0; i < nnMap.length(); ++i ) {
            QDomNode attrNode = nnMap.item(i);
            if ( !attrNode.nodeName().compare("mtime") ) {
                m_mtime = attrNode.toElement().text().toInt();
            }
        }
    }

    return true;
}

#if 0

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
    dir.setFilter(QDir::NoDotAndDotDot | QDir::Files | QDir::Dirs);
    QStringList files = dir.entryList();

    for ( int i = 0; i < files.size(); ++i ) {
        QString file = files.at(i);
        // qDebug () << file;
        ObservedPathPointer observedPath = new ObservedPath(file);
        observedPath->setObservedPathStat();
        observedPathVec.push_back(observedPath);

        if ( observedPath->isDirFile() ) {
            observedPath->traverseObservedPath(observedPathVec);
        }
    }
}

#endif

};

