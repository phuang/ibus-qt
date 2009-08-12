#ifndef _Q_IBUS_OBSERVED_PATH_H_
#define _Q_IBUS_OBSERVED_PATH_H_

#include <QDir>
#include <QDebug>
#include <QDateTime>
#include <QXmlStreamWriter>
#include <QtXml/QDomNode>
#include "qibusserializable.h"

namespace IBus {

class ObservedPath;
typedef Pointer<ObservedPath> ObservedPathPointer;

class ObservedPath : public Serializable
{
    Q_OBJECT;

public:
    ObservedPath ()
    {}
    ObservedPath (QString path): m_path(path)
    {}

    ~ObservedPath () {}

public:
    virtual bool serialize (QDBusArgument &argument) const;
    virtual bool deserialize (const QDBusArgument &argument);

public:
    bool parseXmlNode (const QDomNode & node);
    bool isObservedPathModified () const;
    void setObservedPathStat ();
    void traverseObservedPath (QVector<ObservedPathPointer> & observedPathVec) const;

    const QString & getPath() const { return m_path; }
    const int getMTime() const { return m_mtime; }

    bool isRegularFile() const
    {
        QFileInfo fi(m_path);
        return fi.isFile();
    }

    bool isDirFile() const
    {
        QFileInfo fi(m_path);
        return fi.isDir();
    }

private:
    QString m_path;
    uint    m_mtime;
    bool    m_isDir;
    bool    m_isExist;

    IBUS_SERIALIZABLE
};

};

#endif
