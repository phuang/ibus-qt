#ifndef __Q_IBUS_LOOKUP_TABLE_H_
#define __Q_IBUS_LOOKUP_TABLE_H_

#include "qibusserializable.h"

namespace IBus {

class LookupTable;
typedef Pointer<LookupTable> LookupTablePointer;

class LookupTable: public Serializable
{
    Q_OBJECT;

public:
    LookupTable() {}
    LookupTable(uint pagesize,
                uint cursorPos,
                bool cursorVisible,
                bool round,
                QVector<QString> * candidates,
                QVector<QString> * table)
    {
        m_pagesize = pagesize;
        m_cursorPos = cursorPos;
        m_cursorVisible = cursorVisible;
        m_round = round;
        m_candidates = candidates;
        m_table = table;
    }

    ~LookupTable() {}

private:
    virtual bool serialize(QDBusArgument & argument) const;
    // virtual bool deserialize(const QDBusArgument &argument);

private:
    uint        m_pagesize;
    uint        m_cursorPos;
    bool        m_cursorVisible;
    bool        m_round;
    QVector<TextPointer>   m_candidates;
    QVector<TextPointer>   m_table;
    /*
    QVector<LookupTablePointer>   *   m_candidates;
    QVector<LookupTablePointer>   *   m_table;
    */

    IBUS_SERIALIZABLE
};

};

#endif
