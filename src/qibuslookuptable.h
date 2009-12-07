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
                 uint pageSize = 5,
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

    TextPointer candidate (uint index) const;
    TextPointer label (const uint index) const;
    const QVector<TextPointer> & candidates () const { return m_candidates; }
    const QVector<TextPointer> & labels () const { return m_labels; }
    uint cursorPos () const { return m_cursorPos; }
    uint pageSize () const {return m_pageSize; }
    bool isCursorVisible () const { return m_cursorVisible; }
    bool isRound () const { return m_round; }

    void setCursorPos (const uint cursorPos);
    void setCursorVisible (bool visible);
    void setPageSize (uint pageSize);
    uint cursorPosInPage () const;
    void clean (void);

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
