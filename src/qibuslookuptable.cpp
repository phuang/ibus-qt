#include "qibuslookuptable.h"

namespace IBus {

IBUS_DECLARE_SERIALIZABLE(LookupTable, IBusLookupTable);

bool
LookupTable::serialize (QDBusArgument & argument) const
{
    if ( !Serializable::serialize(argument) )
        return false;

    // read variables of basic type into argument
    argument << m_pageSize;
    argument << m_cursorPos;
    argument << m_cursorVisible;
    argument << m_round;

    // read variables of container type into argument
    argument.beginArray(QDBusArgument::VariantType);
    for ( int i = 0; i < m_candidates.size(); ++i )
    {
        argument << m_candidates[i];
    }
    argument.endArray();

    argument.beginArray(QDBusArgument::VariantType);
    for ( int i = 0; i < m_labels.size(); ++i )
    {
        argument << m_labels[i];
    }
    argument.endArray();

    return true;
}

bool
LookupTable::deserialize (const QDBusArgument & argument)
{
    if ( !Serializable::deserialize(argument) )
        return false;

    // clear vector
    m_candidates.clear();
    m_labels.clear();

    argument >> m_pageSize;
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
        m_labels.append(tp);
    }
    argument.endArray();

    return true;
}

void
LookupTable::appendCandidate(const TextPointer & e)
{
    m_candidates.append(e);
}

void
LookupTable::appendLabel(const TextPointer & e)
{
    m_labels.append(e);
}

TextPointer
LookupTable::getCandidate(const uint index) const
{
    if ( index >= static_cast<uint>(m_candidates.size()) )
        return NULL;

    return m_candidates[index];
}

TextPointer
LookupTable::getLabel(const uint index) const
{
    if ( index >= static_cast<uint>(m_labels.size()) )
        return NULL;

    return m_labels[index];
}

void
LookupTable::setCursorPos(const uint cursorPos)
{
    m_cursorPos = cursorPos;
}

uint
LookupTable::cursorPosInPage() const
{
    return (m_cursorPos % m_pageSize);
}

void
LookupTable::setCursorVisible(bool visible)
{
    m_cursorVisible = visible;
}

void
LookupTable::setPageSize(const uint pageSize)
{
    m_pageSize = pageSize;
}

bool
LookupTable::pageUp()
{
    if ( m_cursorPos >= m_pageSize )
    {
        m_cursorPos -= m_pageSize;
        return true;
    }

    // here, cursor points to first page
    if ( !m_round )
        return false;

    // set the right position of cursor  
    uint tmpCursorPos = (m_candidates.size() / m_pageSize) * m_pageSize + cursorPosInPage();
    if ( tmpCursorPos >= static_cast<uint>(m_candidates.size()) )
        m_cursorPos = m_candidates.size() - 1;
    else
        m_cursorPos = tmpCursorPos;
        
    return true;
}

bool
LookupTable::pageDown()
{
    if ( (m_candidates.size() / m_pageSize) > (m_cursorPos / m_pageSize) )
    {
        if ( (m_cursorPos + m_pageSize) < static_cast<uint>(m_candidates.size()) )
            m_cursorPos = m_cursorPos + m_pageSize;
        else
            m_cursorPos = ((m_cursorPos / m_pageSize) * m_pageSize) + cursorPosInPage();

        return true;
    }

    // curosr points to last page
    if ( !m_round )
        return false;

    m_cursorPos = m_cursorPos % m_pageSize;
    return true;
}

bool
LookupTable::cursorUp()
{
    if ( m_cursorPos == 0 )
    {
        // cursor points to the first candidate of first page
        if ( !m_round )
            return false;

        m_cursorPos = m_candidates.size() - 1;
        return true;
    }

    --m_cursorPos;
    return true;
}

bool
LookupTable::cursorDown()
{
    if ( m_cursorPos == (static_cast<uint>(m_candidates.size()) - 1) )
    {
        // cursor points to the last candidate of last page
        if ( !m_round )
            return false;

        m_cursorPos = 0;
        return true;
    }

    ++m_cursorPos;
    return true;
}

};
