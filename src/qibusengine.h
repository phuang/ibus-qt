#ifndef _Q_IBUS_ENGINE_H_
#define _Q_IBUS_ENGINE_H_

#include <QObject>
#include <QDBusVariant>
#include "qibustypes.h"
#include "qibusobject.h"

namespace IBus {

class Engine;
typedef Pointer<Engine> EnginePointer;

class Engine : public Object
{
    Q_OBJECT;

public :
    Engine () {}
    Engine (bool enabled, bool hasFocus);
    ~Engine () {}

public :

public :
    // IME developpers need to implement following functions
    virtual void candidateClicked(uint index, uint button, uint state) = 0;
    virtual void cursorDown() = 0;
    virtual void cursorUp() = 0;
    virtual void destroy() = 0;
    virtual void disable() = 0;
    virtual void enable() = 0;
    virtual void focusIn() = 0;
    virtual void focusOut() = 0;
    virtual void pageDown() = 0;
    virtual void pageUp() = 0;
    virtual bool processKeyEvent(uint keyval, uint keycode, uint state) = 0;
    virtual void propertyActivate(const QString &prop_name, int prop_state) = 0;
    virtual void propertyHide(const QString &prop_name) = 0;
    virtual void propertyShow(const QString &prop_name) = 0;
    virtual void reset() = 0;
    virtual void setCapabilities(uint cap) = 0;
    virtual void setCursorLocation(int x, int y, int w, int h) = 0;

public slots :
    void CandidateClicked(uint index, uint button, uint state);
    void CursorDown();
    void CursorUp();
    void Destroy();
    void Disable();
    void Enable();
    void FocusIn();
    void FocusOut();
    void PageDown();
    void PageUp();
    bool ProcessKeyEvent(uint keyval, uint keycode, uint state);
    void PropertyActivate(const QString &prop_name, int prop_state);
    void PropertyHide(const QString &prop_name);
    void PropertyShow(const QString &prop_name);
    void Reset();
    void SetCapabilities(uint cap);
    void SetCursorLocation(int x, int y, int w, int h); 

signals :
    void CommitText(const QDBusVariant &text);
    void CursorDownLookupTable();
    void CursorUpLookupTable();
    void ForwardKeyEvent(uint keyval, uint state);
    void HideAuxiliaryText();
    void HideLookupTable();
    void HidePreeditText();
    void PageDownLookupTable();
    void PageUpLookupTable();
    void RegisterProperties(const QDBusVariant &props);
    void ShowAuxiliaryText();
    void ShowLookupTable();
    void ShowPreeditText();
    void UpdateAuxiliaryText(const QDBusVariant &text, bool visible);
    void UpdateLookupTable(const QDBusVariant &lookup_table, bool visible);
    void UpdatePreeditText(const QDBusVariant &text, uint cursor_pos, bool visible);
    void UpdateProperty(const QDBusVariant &prop);

private :
    bool m_enabled;
    bool m_hasFocus;

    Rectangle   m_cursorArea;
    uint        m_clientCapabilities;
};

};

#endif
