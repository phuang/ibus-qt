#ifndef __Q_IBUS_INPUT_CONTEXT_H_
#define __Q_IBUS_INPUT_CONTEXT_H_

#include "qibusbus.h"
#include "qibustext.h"
#include "qibusproperty.h"
#include "qibuslookuptable.h"

class InputContextAdaptor;

namespace IBus {

class InputContextProxy;
class InputContext;
typedef Pointer<InputContext> InputContextPointer;

class InputContext : public Object
{
    Q_OBJECT;

protected:

public:
    InputContext (void);
    ~InputContext (void);

    void reste (void);
    void destroy (void);
    void enable (void);
    void disable (void);
    void focusIn (void);
    void focusOut (void);
    void getEngine (void);
    bool isEnabled (void);
    bool processKeyEvent (uint keyval, uint keycode, uint state);
    void setCapabilities (uint caps);
    void setCursorLocation (int x, int y, int w, int h);
    void setEngine (const QString &name);

public:
    static InputContextPointer create (const BusPointer &bus);

Q_SIGNALS:
    void commitText (const TextPointer &text);
    void enabled (void);
    void disabled (void);
    void forwardKeyEvent (uint keyval, uint keycode, uint state);
    void updatePreeditText (const TextPointer &text, uint cursor_pos, bool visible);
    void showPreeditText (void);
    void hidePreeditText (void);
    void updateAuxiliaryText (const TextPointer &text, bool visible);
    void showAuxiliaryText (void);
    void hideAuxiliaryText (void);
    void updateLookupTable (const LookupTablePointer &table, bool visible);
    void showLookupTable (void);
    void hideLookupTable (void);
    void cursorUpLookupTable (void);
    void cursorDownLookupTable (void);
    void pageUpLookupTable (void);
    void pageDownLookupTable (void);
    void registerProperties (const QList<PropertyPointer> &props);
    void updateProperty (const PropertyPointer &property);

private:

/*
signals:
    void disconnected (void);
    void connected (void);

private slots:
    void slotAddressChanged (const QString &path);
    void slotIBusDisconnected (void);
*/
private:
    InputContextProxy *m_context;
};

};

#endif
