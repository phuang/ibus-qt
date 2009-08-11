#include <QXmlStreamWriter>
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

void
ObservedPath::output (QString & output)
{
    QXmlStreamWriter stream(&output);
    stream.setAutoFormatting(true);

    stream.writeStartElement("path");

    QString mtime;
    mtime.number(m_mtime);
    stream.writeAttribute("mtime", mtime);

    stream.writeCharacters(m_path);
    stream.writeEndElement();

    stream.writeEndDocument();
}

bool ObservedPath::parseObservedPath (const QDomNode & node)
{ return true; }

const ObservedPathPointer newObserverdPathFromXmlNode (const QDomNode & node)
{
    return NULL;
}

};
