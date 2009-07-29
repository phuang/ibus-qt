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

bool LookupTable::deserialize (const QDBusArgument & argument)
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

void LookupTable::setCursorPos(const uint cursorPos)
{
    m_cursorPos = cursorPos;
}

uint LookupTable::getCursorPos() const
{
    return m_cursorPos;
}

uint LookupTable::getCursorPosInPage() const
{
    return (m_cursorPos % m_pagesize);
}

void LookupTable::setCursorVisible(bool visible)
{
    m_cursorVisible = visible;
}

bool LookupTable::isCursorVisible() const
{
    return m_cursorVisible;
}

void LookupTable::setPageSize(const uint pagesize)
{
    m_pagesize = pagesize;
}

uint LookupTable::getPageSize() const
{
    return m_pagesize;
}

bool LookupTable::pageUp()
{
    if ( m_cursorPos >= m_pagesize )
    {
        m_cursorPos -= m_pagesize;
        return true;
    }

    // here, cursor points to first page
    if ( !m_round )
        return false;

    // set the right position of cursor  
    uint tmpCursorPos = (m_candidates.size() / m_pagesize) * m_pagesize + getCursorPosInPage();
    if ( tmpCursorPos >= m_candidates.size() )
        m_cursorPos = m_candidates.size() - 1;
    else
        m_cursorPos = tmpCursorPos;
        
    return true;
}

bool LookupTable::pageDown()
{
    if ( (m_candidates.size() / m_pagesize) > (m_cursorPos / m_pagesize) )
    {
        if ( (m_cursorPos + m_pagesize) < m_candidates.size() )
            m_cursorPos = m_cursorPos + m_pagesize;
        else
            m_cursorPos = ((m_cursorPos / m_pagesize) * m_pagesize) + getCursorPosInPage();

        return true;
    }

    // curosr points to last page
    if ( !m_round )
        return false;

    m_cursorPos = m_cursorPos % m_pagesize;
    return true;
}

bool LookupTable::cursorUp()
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

bool LookupTable::cursorDown()
{
    if ( m_cursorPos == (m_candidates.size() - 1) )
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
