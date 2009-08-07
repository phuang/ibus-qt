#include <QXmlStreamWriter>
#include "qibusenginedesc.h"

namespace IBus {

IBUS_DECLARE_SERIALIZABLE(EngineDesc, IBusEngineDesc);

bool
EngineDesc::serialize (QDBusArgument &argument) const
{
    if (!Serializable::serialize (argument))
        return false;

    argument << m_name;
    argument << m_longname;
    argument << m_description;
    argument << m_language;
    argument << m_license;
    argument << m_author;
    argument << m_icon;
    argument << m_layout;

    return true;
}

bool
EngineDesc::deserialize (const QDBusArgument &argument)
{
    if (!Serializable::deserialize (argument))
        return false;

    argument >> m_name;
    argument >> m_longname;
    argument >> m_description;
    argument >> m_language;
    argument >> m_license;
    argument >> m_author;
    argument >> m_icon;
    argument >> m_layout;

    return true;
}

// generate xml stream via QT-lib
void
EngineDesc::output (QString & output) const
{
    QXmlStreamWriter stream(&output);
    stream.setAutoFormatting(true);

    stream.writeStartDocument();

    stream.writeStartElement("engine");

    stream.writeTextElement("name", m_name);
    stream.writeTextElement("longname", m_longname);
    stream.writeTextElement("description", m_description);
    stream.writeTextElement("language", m_language);
    stream.writeTextElement("license", m_license);
    stream.writeTextElement("author", m_author);
    stream.writeTextElement("icon", m_icon);
    stream.writeTextElement("layout", m_layout);

    QString stringRank;
    stringRank = stringRank.number(m_rank);
    stream.writeTextElement("rank", stringRank);

    stream.writeEndElement();

    stream.writeEndDocument();
}

bool
EngineDesc::parseXmlNode (const QDomNodePointer node)
{
    QString nodename(node->nodeName());
    if ( nodename.compare("engine") ) {
        return false;
    }

    QDomNode child = node->firstChild();
    for ( ; !child.isNull() ; child = child.nextSibling() ) {
        if ( child.nodeName().compare("name") ) {
            m_memInEngine[child.nodeName()] = true;
            m_name = child.nodeValue();
        }
        else if ( child.nodeName().compare("longname") ) {
            m_memInEngine[child.nodeName()] = true;
            m_longname = child.nodeValue();
        }
        else if ( child.nodeName().compare("description") ) {
            m_memInEngine[child.nodeName()] = true;
            m_description = child.nodeValue();
        }
        else if ( child.nodeName().compare("language") ) {
            m_memInEngine[child.nodeName()] = true;
            m_language = child.nodeValue();
        }
        else if ( child.nodeName().compare("license") ) {
            m_memInEngine[child.nodeName()] = true;
            m_license = child.nodeValue();
        }
        else if ( child.nodeName().compare("author") ) {
            m_memInEngine[child.nodeName()] = true;
            m_author = child.nodeValue();
        }
        else if ( child.nodeName().compare("icon") ) {
            m_memInEngine[child.nodeName()] = true;
            m_icon = child.nodeValue();
        }
        else if ( child.nodeName().compare("layout") ) {
            m_memInEngine[child.nodeName()] = true;
            m_layout = child.nodeValue();
        }
        else if ( child.nodeName().compare("rank") ) {
            m_memInEngine[child.nodeName()] = true;
            m_rank = child.nodeValue().toInt();
        }
    }

    QMapIterator<QString, bool> iter(m_memInEngine);
    while ( iter.hasNext() ) {
        if ( iter.value() == false ) {
            return false;
        }

        iter.next();
    }

    return true;
}

};
