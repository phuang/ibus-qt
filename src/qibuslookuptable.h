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
    LookupTable (bool round,
                 bool cursorVisible = true,
                 uint pageSize = 6,
                 uint cursorPos = 0):
                 m_pageSize (pageSize),
                 m_cursorPos (cursorPos),
                 m_cursorVisible (cursorVisible),
                 m_round (round) {}

    ~LookupTable() {}

public:
    virtual bool serialize (QDBusArgument & argument);
    virtual bool deserialize (const QDBusArgument & argument);
    void appendCandidate (const TextPointer & e);
    void appendLabel (const TextPointer & e);

    TextPointer getCandidate (const uint index) const;
    TextPointer getLabel (const uint index) const;
    const QVector<TextPointer> & getCandidates () const { return m_candidates; }
    const QVector<TextPointer> & getLabels () const { return m_labels; }
    uint getCursorPos () const { return m_cursorPos; }
    uint getPageSize () const {return m_pageSize; }
    bool isCursorVisible () const { return m_cursorVisible; }
    bool isRound () const { return m_round; }

    void setCursorPos (const uint cursorPos);
    void setCursorVisible (bool visible);
    void setPageSize (uint pageSize);
    uint cursorPosInPage () const;

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
