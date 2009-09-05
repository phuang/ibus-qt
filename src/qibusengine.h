#ifndef _Q_IBUS_ENGINE_H_
#define _Q_IBUS_ENGINE_H_

#include <QDBusVariant>
#include "qibustypes.h"
#include "qibustext.h"
#include "qibusproplist.h"
#include "qibuslookuptable.h"

class IBusEngineAdaptor;

namespace IBus {

class Engine;
typedef Pointer<Engine> EnginePointer;

class Engine : public Object
{
    Q_OBJECT

public :
    Engine (const QString &engineName);
    virtual ~Engine ();

public :
    const QString & getEngineName () const;
    void updateLookupTableFast (const LookupTablePointer & lookupTablePtr, bool visible);

public :
    void commitText (const TextPointer & text)
    {
        CommitText(qDBusVariantFromSerializable (text));
    }

    void cursorDownLookupTable ()
    {
        cursorDownLookupTable();
    }

    void cursorUpLookupTable ()
    {
        CursorUpLookupTable();
    }

    void forwardKeyEvent (uint keyval, uint state)
    {
        ForwardKeyEvent(keyval, state);
    }

    void hideAuxiliaryText ()
    {
        HideAuxiliaryText();
    }

    void hideLookupTable ()
    {
        HideLookupTable();
    }

    void hidePreeditText ()
    {
        HidePreeditText();
    }

    void pageDownLookupTable ()
    {
        PageDownLookupTable();
    }

    void pageUpLookupTable ()
    {
        PageUpLookupTable();
    }

    void registerProperties (const PropertyPointer & props)
    {
        RegisterProperties(qDBusVariantFromSerializable(props));
    }

    void showAuxiliaryText ()
    {
        ShowAuxiliaryText();
    }

    void showLookupTable ()
    {
        ShowLookupTable();
    }

    void showPreeditText ()
    {
        ShowPreeditText();
    }

    void updateAuxiliaryText (const TextPointer & text, bool visible)
    {
        UpdateAuxiliaryText(qDBusVariantFromSerializable(text), visible);
    }

    void updateLookupTable (const LookupTablePointer & lookupTable, bool visible)
    {
        UpdateLookupTable(qDBusVariantFromSerializable(lookupTable), visible);
    }

    void updatePreeditText (const TextPointer & text, uint cursorPos, bool visible)
    {
        UpdatePreeditText(qDBusVariantFromSerializable(text), cursorPos, visible);
    }

    void updateProperty (const PropertyPointer & prop)
    {
        UpdateProperty(qDBusVariantFromSerializable(prop));
    }

public :
    // IME developpers need to implement following functions, only processKeyEvent is mandotory
    virtual void candidateClicked (uint index, uint button, uint state);
    virtual void cursorDown ();
    virtual void cursorUp ();
    virtual void destroy ();
    virtual void disable ();
    virtual void enable ();
    virtual void focusIn ();
    virtual void focusOut ();
    virtual void pageDown ();
    virtual void pageUp ();
    virtual bool processKeyEvent (uint keyval, uint keycode, uint state);
    virtual void propertyActivate (const QString &prop_name, int prop_state);
    virtual void propertyHide (const QString &prop_name);
    virtual void propertyShow (const QString &prop_name);
    virtual void reset ();
    virtual void setCapabilities (uint cap);
    virtual void setCursorLocation (int x, int y, int w, int h);

private Q_SLOTS:
    Q_INVOKABLE void CandidateClicked (uint index, uint button, uint state);
    Q_INVOKABLE void CursorDown ();
    Q_INVOKABLE void CursorUp ();
    Q_INVOKABLE void Destroy ();
    Q_INVOKABLE void Disable ();
    Q_INVOKABLE void Enable ();
    Q_INVOKABLE void FocusIn ();
    Q_INVOKABLE void FocusOut ();
    Q_INVOKABLE void PageDown ();
    Q_INVOKABLE void PageUp ();
    Q_INVOKABLE bool ProcessKeyEvent (uint keyval, uint keycode, uint state);
    Q_INVOKABLE void PropertyActivate (const QString &prop_name, int prop_state);
    Q_INVOKABLE void PropertyHide (const QString &prop_name);
    Q_INVOKABLE void PropertyShow (const QString &prop_name);
    Q_INVOKABLE void Reset ();
    Q_INVOKABLE void SetCapabilities (uint cap);
    Q_INVOKABLE void SetCursorLocation (int x, int y, int w, int h);

Q_SIGNALS :
    void CommitText (const QDBusVariant &text);
    void CursorDownLookupTable ();
    void CursorUpLookupTable ();
    void ForwardKeyEvent (uint keyval, uint state);
    void HideAuxiliaryText ();
    void HideLookupTable ();
    void HidePreeditText ();
    void PageDownLookupTable ();
    void PageUpLookupTable ();
    void RegisterProperties (const QDBusVariant &props);
    void ShowAuxiliaryText ();
    void ShowLookupTable ();
    void ShowPreeditText ();
    void UpdateAuxiliaryText (const QDBusVariant &text, bool visible);
    void UpdateLookupTable (const QDBusVariant &lookup_table, bool visible);
    void UpdatePreeditText (const QDBusVariant &text, uint cursor_pos, bool visible);
    void UpdateProperty (const QDBusVariant &prop);

private :
    QString m_engineName;
    IBusEngineAdaptor *m_adaptor;
};

};

#endif
