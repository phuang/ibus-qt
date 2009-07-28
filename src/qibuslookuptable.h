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
    LookupTable() {}
    LookupTable(uint pagesize,
                uint cursorPos,
                bool cursorVisible,
                bool round,
                QVector<TextPointer> candidates,
                QVector<TextPointer> lable): m_candidates(candidates), m_lable(lable)
    {
        m_pagesize = pagesize;
        m_cursorPos = cursorPos;
        m_cursorVisible = cursorVisible;
        m_round = round;
    }

    // copy constructor function
    LookupTable(const LookupTable & other)
    {
        m_pagesize = other.m_pagesize;
        m_cursorPos = other.m_cursorPos;
        m_cursorVisible = other.m_cursorVisible;
        m_round = other.m_round;
        m_candidates = other.m_candidates;
        m_lable = other.m_lable;
    }

    LookupTable & operator=(const LookupTable & other)
    {
        if ( this == &other )
            return *this;

        m_pagesize = other.m_pagesize;
        m_cursorPos = other.m_cursorPos;
        m_cursorVisible = other.m_cursorVisible;
        m_round = other.m_round;
        m_candidates = other.m_candidates;
        m_lable = other.m_lable;

        return *this;
    }

    ~LookupTable() {}

private:
    virtual bool serialize(QDBusArgument & argument) const;
    virtual bool deserialize(const QDBusArgument &argument);

    void appendCandidate(const TextPointer & e);
    void appendLable(const TextPointer & e);
    TextPointer getCandidate(const uint index) const;
    TextPointer getLable(const uint index) const;
    void setCursorPos(const uint cursorPos);
    uint getCursorPos() const;
    uint getCursorPosInPage() const;
    void setCursorVisible(bool visible);
    bool isCursorVisible() const;
    void setPageSize(uint pagesize);
    uint getPageSize() const;

    bool pageUp();
    bool pageDown();

    // void initialize() {}     // no need to implement
    // void destroy() {}        // no need to implement

private:
    uint        m_pagesize;
    uint        m_cursorPos;
    bool        m_cursorVisible;
    bool        m_round;

    QVector<TextPointer>    m_candidates;
    QVector<TextPointer>    m_lable;

    IBUS_SERIALIZABLE
};

};

#endif
