#include "qibuslookuptable.h"

namespace IBus {

IBUS_DECLARE_SERIALIZABLE(LookupTable, IBusLookupTable);

bool LookupTable::serialize(QDBusArgument & argument) const
{
    argument.beginStructure();

    // read variables of basic type(non-container).
    argument << m_pagesize;
    argument << m_cursorPos;
    argument << m_cursorVisible;
    argument << m_round;

    // read container variables
    argument.beginArray(QDBusArgument::VariantType);

    for ( int i=0; i < m_candidates->size(); ++i )
    {
        argument << m_candidates[i];
    }

    for ( int i=0; i < m_table->size(); ++i )
    {
        argument << m_table[i];
    }

    argument.endArray();
    argument.endStructure();

    return true;
}

/*
bool LookupTable::deserialize (const QDBusArgument &argument)
{}
*/

};
