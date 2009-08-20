#include "qibusengine.h"

namespace IBus {

Engine::Engine (bool enabled, bool hasFocus)
{
    m_enabled = enabled;
    m_hasFocus = hasFocus;
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

void
Engine::propertyActivate (const QString &prop_name, int prop_state)
{}

void
Engine::propertyHide (const QString &prop_name)
{}

void
Engine::propertyShow (const QString &prop_name)
{}

void
Engine::reset ()
{}

void
Engine::setCapabilities (uint cap)
{}

void
Engine::setCursorLocation (int x, int y, int w, int h)
{}

};
