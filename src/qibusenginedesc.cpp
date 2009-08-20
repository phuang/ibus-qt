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

    m_engineInfo.insert("name", m_name);
    m_engineInfo.insert("longname", m_longname);
    m_engineInfo.insert("description", m_description);
    m_engineInfo.insert("language", m_language);
    m_engineInfo.insert("license", m_license);
    m_engineInfo.insert("author", m_author);
    m_engineInfo.insert("icon", m_icon);
    m_engineInfo.insert("layout", m_layout);
    m_engineInfo.insert("rank", 0);

    return true;
}

// generate xml stream via QT-lib
void
EngineDesc::output (QString & output) const
{
    QXmlStreamWriter stream(&output);
    stream.setAutoFormatting(true);

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
}

bool
EngineDesc::parseXmlNode (const QDomNode & node)
{
    if ( node.nodeName().compare("engine") ) {
        return false;
    }

    bool errFlag = false;

    QDomNode child = node.firstChild();
    for ( ; !child.isNull() ; child = child.nextSibling() ) {
        if ( !child.nodeName().compare("name") ) {
            m_name = child.nodeValue();
        }
        else if ( !child.nodeName().compare("longname") ) {
            m_longname = child.nodeValue();
        }
        else if ( !child.nodeName().compare("description") ) {
            m_description = child.nodeValue();
        }
        else if ( !child.nodeName().compare("language") ) {
            m_language = child.nodeValue();
        }
        else if ( !child.nodeName().compare("license") ) {
            m_license = child.nodeValue();
        }
        else if ( !child.nodeName().compare("author") ) {
            m_author = child.nodeValue();
        }
        else if ( !child.nodeName().compare("icon") ) {
            m_icon = child.nodeValue();
        }
        else if ( !child.nodeName().compare("layout") ) {
            m_layout = child.nodeValue();
        }
        else if ( !child.nodeName().compare("rank") ) {
            m_rank = child.nodeValue().toInt();
        }
        else {
            QString s;
            QXmlStreamWriter stream(&s);
            stream.writeTextElement(child.nodeName(), child.nodeValue());
            qDebug() << "EngineDesc::parseXmlNode, Unknown element, \"<" << s << "\"";

            errFlag = true;
            break;
        }
    }

    if ( errFlag ) {
        return false;
    }

    return true;
}

};
