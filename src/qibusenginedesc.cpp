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

// generate xml stream manually, similiar to gtk codes
void
EngineDesc::output (QString & output, const uint indent) const
{
    appendIndent(output, indent);
    output.append("<engine>\n");

    outputEntry(output, "name", m_name, indent + 1);
    outputEntry(output, "longname", m_longname, indent + 1);
    outputEntry(output, "description", m_description, indent + 1);
    outputEntry(output, "language", m_language, indent + 1);
    outputEntry(output, "license", m_license, indent + 1);
    outputEntry(output, "author", m_author, indent + 1);
    outputEntry(output, "icon", m_icon, indent + 1);
    outputEntry(output, "layout", m_layout, indent + 1);

    QString stringRank;
    stringRank = stringRank.number(m_rank);
    outputEntry(output, "rank", stringRank, indent + 1);

    appendIndent(output, indent);
    output.append("<engine>\n");
}

bool
EngineDesc::parseXmlNode (const XMLNode * node)
{
    const QLinkedList<XMLNode> * subNodes = node->subNodes;
    QLinkedListIterator<XMLNode> iter(*subNodes);

    while ( iter.hasNext() )
    {
        XMLNode tmpNodes = iter.next();

        parseEntry(tmpNodes, "name", m_name);
        parseEntry(tmpNodes, "longname", m_longname);
        parseEntry(tmpNodes, "description", m_description);
        parseEntry(tmpNodes, "language", m_language);
        parseEntry(tmpNodes, "license", m_license);
        parseEntry(tmpNodes, "author", m_author);
        parseEntry(tmpNodes, "icon", m_icon);
        parseEntry(tmpNodes, "layout", m_layout);

        if ( !tmpNodes.name.compare("rank") ) {
            m_rank = tmpNodes.text.toUInt();
        }
    }

    return true;
}

};
