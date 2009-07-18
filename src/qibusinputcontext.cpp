#include "qibusinputcontext.h"
#include "qibusinputcontextproxy.h"


namespace IBus {

InputContext::InputContext (const BusPointer &bus, const QString &path)
 : m_bus (bus)
{
    m_context = new InputContextProxy ("org.freedesktop.IBus",
                                       path,
                                       m_bus->getConnection ());
}

InputContext::~InputContext (void)
{
    destroy ();
}

InputContextPointer
InputContext::create (const BusPointer &bus, const QString &name)
{
    Q_ASSERT (!bus.isNull ());
    
    if (!bus->isConnected ()) {
        qWarning ("Bus does not connect!");
        return NULL;
    }

    QString path = bus->createInputContext (name);

    return new InputContext (bus, path);
}


void
InputContext::reset (void)
{
    Q_ASSERT (m_context);
    m_context->Reset ();
}

void
InputContext::destroy (void)
{
    Q_ASSERT (m_context);
    m_context->Destroy ();
    delete m_context;
    m_context = NULL;
}

void
InputContext::enable (void)
{
    Q_ASSERT (m_context);
    m_context->Enable ();
}

void
InputContext::disable (void)
{
    Q_ASSERT (m_context);
    m_context->Disable ();
}

void
InputContext::focusIn (void)
{
    Q_ASSERT (m_context);
    m_context->FocusIn ();
}

void
InputContext::focusOut (void)
{
    Q_ASSERT (m_context);
    m_context->FocusOut ();
}

void
InputContext::getEngine (void)
{
    Q_ASSERT (m_context);
    m_context->GetEngine ();
}

bool
InputContext::isEnabled (void)
{
    Q_ASSERT (m_context);
    return m_context->IsEnabled ();
}

bool
InputContext::processKeyEvent (uint keyval, uint keycode, uint state)
{
    Q_ASSERT (m_context);
    return m_context->ProcessKeyEvent (keyval, keycode, state);
}

void
InputContext::setCapabilities (uint caps)
{
    Q_ASSERT (m_context);
    m_context->SetCapabilities (caps);
}

void
InputContext::setCursorLocation (int x, int y, int w, int h)
{
    Q_ASSERT (m_context);
    m_context->SetCursorLocation (x, y, w, h);
}

void
InputContext::setEngine (const QString &name)
{
    Q_ASSERT (m_context);
    m_context->SetEngine (name);
}

};
