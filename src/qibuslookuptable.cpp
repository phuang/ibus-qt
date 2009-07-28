#include "qibuslookuptable.h"

namespace IBus {

IBUS_DECLARE_SERIALIZABLE(LookupTable, IBusLookupTable);

bool LookupTable::serialize(QDBusArgument & argument) const
{
    if ( !Serializable::serialize(argument) )
        return false;

    argument.beginArray(QDBusArgument::VariantType);

    // read variables of basic type(non-container).
    argument << m_pagesize;
    argument << m_cursorPos;
    argument << m_cursorVisible;
    argument << m_round;

    for ( int i=0; i < m_candidates.size(); ++i )
    {
        argument << m_candidates[i];
    }

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

    argument.beginArray();

    argument >> m_pagesize;
    argument >> m_cursorPos;
    argument >> m_cursorVisible;
    argument >> m_round;

    while ( !argument.atEnd() );
    {
        TextPointer tp;
        argument >> tp;
        m_candidates.append(tp);
    }

    while ( !argument.atEnd() );
    {
        TextPointer tp;
        argument >> tp;
        m_lable.append(tp);
    }
    argument.endArray();

    return true;
}

};
