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
        qWarning () << "InputContext::create:" << "Bus does not connect!";
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

/* slots */
void
InputContext::slotCommitText (const QDBusVariant &text)
{
    commitText (qDBusVariantToSerializable (text));
}

void
InputContext::slotCursorDownLookupTable ()
{
    cursorDownLookupTable ();
}

void
InputContext::slotCursorUpLookupTable ()
{
    cursorUpLookupTable ();
}

void
InputContext::slotDisabled ()
{
    disabled ();
}

void
InputContext::slotEnabled ()
{
    enabled ();
}

void
InputContext::slotForwardKeyEvent (uint keyval, uint keycode, uint state)
{
    forwardKeyEvent (keyval, keycode, state);
}

void
InputContext::slotHideAuxiliaryText ()
{
    hideAuxiliaryText ();
}

void
InputContext::slotHideLookupTable ()
{
    hideLookupTable ();
}

void
InputContext::slotHidePreeditText ()
{
    hidePreeditText ();
}

void
InputContext::slotPageDownLookupTable ()
{
    pageDownLookupTable ();
}

void
InputContext::slotPageUpLookupTable ()
{
    pageUpLookupTable ();
}

void
InputContext::slotRegisterProperties (const QDBusVariant &props)
{
    registerProperties (qDBusVariantToSerializable (props));
}

void
InputContext::slotShowAuxiliaryText ()
{
    showAuxiliaryText ();
}

void
InputContext::slotShowLookupTable ()
{
    showLookupTable ();
}

void
InputContext::slotShowPreeditText ()
{
    showPreeditText ();
}

void
InputContext::slotUpdateAuxiliaryText (const QDBusVariant &text, bool visible)
{
    updateAuxiliaryText (qDBusVariantToSerializable (text), visible);
}

void
InputContext::slotUpdateLookupTable (const QDBusVariant &table, bool visible)
{
    updateLookupTable (qDBusVariantToSerializable (table), visible);
}

void
InputContext::slotUpdatePreeditText (const QDBusVariant &text, uint cursor_pos, bool visible)
{
    updatePreeditText (qDBusVariantToSerializable(text), cursor_pos, visible);
}

void
InputContext::slotUpdateProperty (const QDBusVariant &prop)
{
    updateProperty (qDBusVariantToSerializable (prop));
}

};
