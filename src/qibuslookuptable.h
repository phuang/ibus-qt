#ifndef __Q_IBUS_LOOKUP_TABLE_H_
#define __Q_IBUS_LOOKUP_TABLE_H_

#include "qibusserializable.h"
#include "qibustext.h"

namespace IBus {

class LookupTable;
typedef Pointer<LookupTable> LookupTablePointer;

class LookupTable: public Serializable
{
    Q_OBJECT;

public:
    LookupTable () {}
    LookupTable (uint pageSize,
                 uint cursorPos,
                 bool cursorVisible,
                 bool round,
                 QVector<TextPointer> candidates,
                 QVector<TextPointer> labels)
    : m_pageSize (pageSize),
      m_cursorPos (cursorPos),
      m_cursorVisible (cursorVisible),
      m_round (round),
      m_candidates (candidates),
      m_labels (labels)
    {
    }

/*
    // copy constructor function
    LookupTable (const LookupTablePointer &table)
    {
        m_pageSize = table->m_pageSize;
        m_cursorPos = table->m_cursorPos;
        m_cursorVisible = table->m_cursorVisible;
        m_round = table->m_round;
        m_candidates = table->m_candidates;
        m_label = table->m_lable;
    }

    LookupTablePointer & operator= (const LookupTablePointer &table)
    {
        if ( this == table )
            return this;

        m_pageSize = other.m_pageSize;
        m_cursorPos = other.m_cursorPos;
        m_cursorVisible = other.m_cursorVisible;
        m_round = other.m_round;
        m_candidates = other.m_candidates;
        m_label = other.m_lable;

        return this;
    }
*/
    ~LookupTable() {}

public:
    virtual bool serialize (QDBusArgument & argument) const;
    virtual bool deserialize (const QDBusArgument & argument);
    void appendCandidate (const TextPointer & e);
    void appendLabel (const TextPointer & e);
    TextPointer getCandidate (const uint index) const;
    TextPointer getLabel (const uint index) const;
    void setCursorPos (const uint cursorPos);
    uint cursorPos () const { return m_cursorPos; }
    uint cursorPosInPage () const;
    void setCursorVisible (bool visible);
    bool isCursorVisible () const { return m_cursorVisible; }
    void setPageSize (uint pageSize);
    uint pageSize () const {return m_pageSize; }

    bool pageUp();
    bool pageDown();
    bool cursorUp();
    bool cursorDown();

private:
    uint        m_pageSize;
    uint        m_cursorPos;
    bool        m_cursorVisible;
    bool        m_round;

    QVector<TextPointer>    m_candidates;
    QVector<TextPointer>    m_labels;

    IBUS_SERIALIZABLE
};

};

#endif
