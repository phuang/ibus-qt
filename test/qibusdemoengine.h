#ifndef __Q_IBUS_HANGUL_ENGINE_H_
#define __Q_IBUS_HANGUL_ENGINE_H_
 
#include <hangul-1.0/hangul.h>
#include <qibus.h>
 
using namespace IBus;
 
class DemoEngine : public Engine
{
    Q_OBJECT
 
public :
    Q_INVOKABLE DemoEngine (const QString &name);
 
    virtual ~DemoEngine ();
 
public :
    void initialize ();
    void clearup ();

private :
    // send signals
    void UpdatePreeditText ();
    void UpdateAuxiliaryText ();
    void UpdateLookupTable ();
    void CommitCurrentCandidate ();

private :
    void propertyActivate (const QString &prop_name, int prop_state);
    void closeLookupTable ();

private :
    // virtual function
    bool processKeyEvent (uint keyval, uint keycode, uint state);
 
private :
 
    QString             m_context;  // store keyboard input

    LookupTablePointer  m_lookupTable;
    PropertyPointer     m_prop;
    PropListPointer     m_propList;
};
 
#endif
