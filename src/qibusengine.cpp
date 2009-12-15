#include "qibusengine.h"
#include "qibusengineadaptor.h"

namespace IBus {

Engine::Engine (const QString &engineName)
    : m_engineName(engineName)
{
    m_adaptor = new IBusEngineAdaptor (this);
    if ( !m_adaptor ) {
        qDebug () << "Engine::Engine, new IBusEngineAdaptor error!";
    }
}

Engine::~Engine ()
{
    if( NULL != m_adaptor ) {
        delete m_adaptor;
        m_adaptor = NULL;
    }
}

const QString &
Engine::engineName () const
{
    return m_engineName;
}

void
Engine::updateLookupTableFast (const LookupTablePointer & lookupTablePtr, bool visible)
{
    if ( static_cast<uint>(lookupTablePtr->candidates().size()) <= (lookupTablePtr->pageSize() << 2) ) {
        updateLookupTable(lookupTablePtr, visible);
        return ;
    }

    LookupTable newLookupTable(lookupTablePtr->pageSize(), 0, lookupTablePtr->isCursorVisible(), lookupTablePtr->isRound());
    uint pageNumBegin = lookupTablePtr->cursorPos() / lookupTablePtr->pageSize();

    for ( int i = 0; i < (lookupTablePtr->candidates().size()) \
                    && i < static_cast<int>(pageNumBegin * lookupTablePtr->pageSize() + lookupTablePtr->pageSize()); ++i ) {
        newLookupTable.appendCandidate (lookupTablePtr->candidate (i));
    }

    newLookupTable.setCursorPos (lookupTablePtr->cursorPos ());
    updateLookupTable (static_cast<LookupTablePointer>(&newLookupTable), visible);
}

void
Engine::CandidateClicked (uint index, uint button, uint state)
{
    candidateClicked(index, button, state);
}

void
Engine::CursorDown ()
{
    cursorDown();
}

void
Engine::CursorUp ()
{
    cursorUp();
}

void
Engine::Destroy ()
{
    destroy();
}

void
Engine::Disable ()
{
    disable();
}

void
Engine::Enable ()
{
    enable();
}

void
Engine::FocusIn()
{
    focusIn();
}

void
Engine::FocusOut()
{
    focusOut();
}

void
Engine::PageDown()
{
    pageDown();
}

void
Engine::PageUp()
{
    pageUp();
}

bool
Engine::ProcessKeyEvent(uint keyval, uint keycode, uint state)
{
    return processKeyEvent(keyval, keycode, state);
}

void
Engine::PropertyActivate(const QString &prop_name, int prop_state)
{
    qDebug () << "Engine::PropertyActivate";

    propertyActivate(prop_name, prop_state);
}

void
Engine::PropertyHide(const QString &prop_name)
{
    propertyHide(prop_name);
}

void
Engine::PropertyShow(const QString &prop_name)
{
    propertyShow(prop_name);
}

void
Engine::Reset()
{
    reset();
}

void
Engine::SetCapabilities(uint cap)
{
    setCapabilities(cap);
}

void
Engine::SetCursorLocation(int x, int y, int w, int h)
{
    setCursorLocation(x, y, w, h);
}

// IME developpers need to implement following functions
void
Engine::candidateClicked (uint index, uint button, uint state)
{}

void
Engine::cursorDown ()
{}

void
Engine::cursorUp ()
{}

void
Engine::destroy ()
{}

void
Engine::disable ()
{}

void
Engine::enable ()
{}

void
Engine::focusIn ()
{}

void
Engine::focusOut ()
{}

void
Engine::pageDown ()
{}

void
Engine::pageUp ()
{}

bool
Engine::processKeyEvent (uint keyval, uint keycode, uint state)
{
    return true;
}

void
Engine::propertyActivate (const QString &prop_name, int prop_state)
{
}

void
Engine::propertyHide (const QString &prop_name)
{
}

void
Engine::propertyShow (const QString &prop_name)
{
}

void
Engine::reset ()
{
}

void
Engine::setCapabilities (uint cap)
{
}

void
Engine::setCursorLocation (int x, int y, int w, int h)
{
}

};
