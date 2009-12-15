#ifndef __Q_IBUS_ENGINE_H_
#define __Q_IBUS_ENGINE_H_

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
    /**
     * @brief Constructor of Engine object.
     *
     * @return
     */
    Engine (const QString &engineName);

    /**
     * @brief Destructor of Engine object.
     *
     * @return
     */
    virtual ~Engine ();

public :
    /**
     * @brief Gets name of the engine object.
     *
     * @return The name of the engine object.
     */
    const QString & engineName () const;

    /**
     * @brief Updates the lookup table in fast mode, it only sends candidates in current page.
     *
     * @param[in] lookupTable A lookup table object.
     * @param[in] visible Whether the  lookup table is visible.
     * @return
     */
    void updateLookupTableFast (const LookupTablePointer & lookupTable, bool visible);

public :
    /**
     * @brief Commits text to client application.
     *
     * @param[in] text A text object.
     * @return
     */
    void commitText (const TextPointer & text)
    {
        QDBusVariant variant;
        CommitText (qDBusVariantFromSerializable (text, variant));
    }

    /**
     * @brief Moves down the cursor of lookup table.
     *
     * @return
     */
    void cursorDownLookupTable ()
    {
        CursorDownLookupTable();
    }

    /**
     * @brief Moves up the cursor of lookup table.
     *
     * @return
     */
    void cursorUpLookupTable ()
    {
        CursorUpLookupTable();
    }

    /**
     * @brief Forwards keyevents to client application.
     *
     * @param[in] keyval
     * @param[in] keycode
     * @param[in] state
     * @return
     */
    void forwardKeyEvent (uint keyval, uint keycode, uint state)
    {
        ForwardKeyEvent(keyval, keycode, state);
    }

    /**
     * @brief Hides the auxiliary text in UI.
     *
     * @return
     */
    void hideAuxiliaryText ()
    {
        HideAuxiliaryText();
    }

    /**
     * @brief Hides the lookup table in UI.
     *
     * @return
     */
    void hideLookupTable ()
    {
        HideLookupTable();
    }

    /**
     * @brief Hides the preedit text in UI.
     *
     * @return
     */
    void hidePreeditText ()
    {
        HidePreeditText();
    }

    /**
     * @brief Page down the lookup table.
     *
     * @return
     */
    void pageDownLookupTable ()
    {
        PageDownLookupTable();
    }

    /**
     * @brief Page up the lookup table.
     *
     * @return
     */
    void pageUpLookupTable ()
    {
        PageUpLookupTable();
    }

    /**
     * @brief Registers properties.
     *
     * @param[in] props A PropList object contains some properties.
     * @return
     */
    void registerProperties (const PropListPointer & props)
    {
        QDBusVariant variant;
        RegisterProperties(qDBusVariantFromSerializable (props, variant));
    }

    /**
     * @brief Shows the auxiliary text in UI.
     *
     * @return
     */
    void showAuxiliaryText ()
    {
        ShowAuxiliaryText();
    }

    /**
     * @brief Shows the lookup table in UI.
     *
     * @return
     */
    void showLookupTable ()
    {
        ShowLookupTable();
    }

    /**
     * @brief Shows the preedit text in UI.
     *
     * @return
     */
    void showPreeditText ()
    {
        ShowPreeditText();
    }

    /**
     * @brief Updates the auxiliary text.
     *
     * @param[in] text A text object.
     * @param[in] visible Whether the auxiliary text is visible.
     * @return
     */
    void updateAuxiliaryText (const TextPointer & text, bool visible)
    {
        QDBusVariant variant;
        UpdateAuxiliaryText (qDBusVariantFromSerializable (text, variant), visible);
    }

    /**
     * @brief Updates the lookup table.
     *
     * @param[in] lookupTable A lookup table object.
     * @param[in] visible Whether the lookup table is visible.
     * @return
     */
    void updateLookupTable (const LookupTablePointer & lookupTable, bool visible)
    {
        QDBusVariant variant;
        UpdateLookupTable (qDBusVariantFromSerializable (lookupTable, variant), visible);
    }

    /**
     * @brief Updates the preedit text.
     *
     * @param[in] text A text object.
     * @param[in] cursorPos The cursor position in the given text.
     * @param[in] visible Whether the preedit text is visible.
     * @return
     */
    void updatePreeditText (const TextPointer & text, uint cursorPos, bool visible)
    {
        QDBusVariant variant;
        UpdatePreeditText (qDBusVariantFromSerializable (text, variant), cursorPos, visible);
    }

    /**
     * @brief Updates the property
     *
     * @param[in] prop A propeerty object
     * @return
     */
    void updateProperty (const PropertyPointer & prop)
    {
        QDBusVariant variant;
        UpdateProperty (qDBusVariantFromSerializable (prop, variant));
    }

public:
    /**
     * @brief Candidate is clicked.
     *
     *  Implement this virtual function to handle candidate clicked event.
     * @param[in] index The index of candidate clicked
     * @param[in] button The button of the clicked event.
     * @param[in] state The current state of keyboard.
     * @return
     */
    virtual void candidateClicked (uint index, uint button, uint state);

    /**
     * @brief Cursor is moved down.
     *
     * @return
     */
    virtual void cursorDown ();

    /**
     * @brief Cursor is moved up.
     *
     * @return
     */
    virtual void cursorUp ();
    virtual void destroy ();

    /**
     * @brief Disables the engine.
     *
     * @return
     */
    virtual void disable ();

    /**
     * @brief Enables the engine.
     *
     * @return
     */
    virtual void enable ();

    /**
     * @brief Sets the focus of the engine.
     *
     * @return
     */
    virtual void focusIn ();

    /**
     * @brief Unsets the focus of the engine.
     *
     * @return
     */
    virtual void focusOut ();

    /**
     * @brief Moves cursor of lookup table to next page.
     *
     * @return
     */
    virtual void pageDown ();

    /**
     * @brief Moves cursor of lookup tabele to previous page.
     *
     * @return
     */
    virtual void pageUp ();

    /**
     * @brief Moves cursor of lookup tabele to previous page.
     *
     * @param[in] keyval The keyval of the key event.
     * @param[in] keycode The keycode of the key event.
     * @param[in] state The modifiers of the key event.
     * @return If engine returns true, the client application will ignore this key event,
     * otherwise client application will continue process this key event.
     */
    virtual bool processKeyEvent (uint keyval, uint keycode, uint state);

    /**
     * @brief The property with given name is clicked.
     *
     * @param[in] prop_name The name of the property.
     * @param[in] prop_state The state of the property.
     * @return
     */
    virtual void propertyActivate (const QString &prop_name, int prop_state);

    /**
     * @brief Hides the property with given name.
     *
     * @param[in] prop_name The name of the property.
     * @return
     */
    virtual void propertyHide (const QString &prop_name);

    /**
     * @brief Shows the property with given name.
     *
     * @param[in] prop_name The name of the property.
     * @return
     */
    virtual void propertyShow (const QString &prop_name);

    /**
     * @brief Resets the engine.
     *
     * @return
     */
    virtual void reset ();

    /**
     * @brief Sets the capabilities from client application.
     *
     * @param[in] cap The capabilities of client application.
     * @return
     */
    virtual void setCapabilities (uint cap);

    /**
     * @brief Sets the cursor location from client applicaion.
     *
     * @param[in] x
     * @param[in] y
     * @param[in] w
     * @param[in] h
     * @return
     */
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
    /**
     * FIXME need hide signals in doxygen
     */
    void CommitText (const QDBusVariant &text);
    void CursorDownLookupTable ();
    void CursorUpLookupTable ();
    void ForwardKeyEvent (uint keyval, uint keycode, uint state);
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
