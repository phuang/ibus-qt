#include "qibuslookuptable.h"

namespace IBus {

IBUS_DECLARE_SERIALIZABLE(LookupTable, IBusLookupTable);

bool LookupTable::serialize(QDBusArgument & argument) const
{
    if ( !Serializable::serialize(argument) )
        return false;

    // read variables of basic type into argument
    argument << m_pagesize;
    argument << m_cursorPos;
    argument << m_cursorVisible;
    argument << m_round;

    // read variables of container type into argument
    argument.beginArray(QDBusArgument::VariantType);
    for ( int i=0; i < m_candidates.size(); ++i )
    {
        argument << m_candidates[i];
    }
    argument.endArray();

    argument.beginArray(QDBusArgument::VariantType);
    for ( int i=0; i < m_lable.size(); ++i )
    {
        argument << m_lable[i];
    }
    argument.endArray();

    return true;
}

bool LookupTable::deserialize (const QDBusArgument &argument)
{
    if ( !Serializable::deserialize(argument) )
        return false;

    // clear vector
    m_candidates.clear();
    m_lable.clear();

    argument >> m_pagesize;
    argument >> m_cursorPos;
    argument >> m_cursorVisible;
    argument >> m_round;

    argument.beginArray();
    while ( !argument.atEnd() );
    {
        TextPointer tp;
        argument >> tp;
        m_candidates.append(tp);
    }
    argument.endArray();

    argument.beginArray();
    while ( !argument.atEnd() );
    {
        TextPointer tp;
        argument >> tp;
        m_lable.append(tp);
    }
    argument.endArray();

    return true;
}

void LookupTable::appendCandidate(const TextPointer & e)
{
    m_candidates.append(e);
}

void LookupTable::appendLable(const TextPointer & e)
{
    m_lable.append(e);
}

TextPointer LookupTable::getCandidate(const uint index) const
{
    if ( index >= m_candidates.size() )
        return NULL;

    return m_candidates[index];
}

TextPointer LookupTable::getLable(const uint index) const
{
    if ( index >= m_lable.size() )
        return NULL;

    return m_lable[index];
}

};
