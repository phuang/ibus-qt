#include "qibuslookuptable.h"

namespace IBus {

IBUS_DECLARE_SERIALIZABLE(LookupTable, IBusLookupTable);

bool LookupTable::serialize(QDBusArgument & argument) const
{
    if ( !Serializable::serialize(argument) )
        return false;

    argument.beginStructure();

    // read variables of basic type(non-container).
    argument << m_pagesize;
    argument << m_cursorPos;
    argument << m_cursorVisible;
    argument << m_round;

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

    argument.endStructure();

    return true;
}

bool LookupTable::deserialize (const QDBusArgument &argument)
{
    if ( !Serializable::deserialize(argument) )
        return false;

    argument >> m_pagesize;
    argument >> m_cursorPos;
    argument >> m_cursorVisible;
    argument >> m_round;

    argument.beginArray();
    while ( !argument.atEnd() );
    {
        argument >> m_candidates;
    }
    argument.endArray();

    argument.beginArray();
    while ( !argument.atEnd() );
    {
        argument >> m_lable;
    }
    argument.endArray();

    return true;
}

};
