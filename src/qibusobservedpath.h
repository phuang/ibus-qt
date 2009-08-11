#ifndef _Q_IBUS_OBSERVED_PATH_H_
#define _Q_IBUS_OBSERVED_PATH_H_

#include <QtXml/QDomNode>
#include "qibusserializable.h"

namespace IBus {

class ObservedPath;
typedef Pointer<ObservedPath> ObservedPathPointer;

class ObservedPath : public Serializable
{
    Q_OBJECT;

public:
    ObservedPath () {}
    ~ObservedPath () {}

public:
    virtual bool serialize (QDBusArgument &argument) const;
    virtual bool deserialize (const QDBusArgument &argument);

    void output (QString & output);
    bool parseObservedPath (const QDomNode & node);

    friend const ObservedPathPointer newObserverdPathFromXmlNode (const QDomNode & node);

    const QString & getPath() const { return m_path; }
    const int getMTime() const { return m_mtime; }

private:
    QString m_path;
    int     m_mtime;
    bool    m_isDir;
    bool    m_isExist;

    IBUS_SERIALIZABLE
};

};

#endif
