#ifndef __Q_IBUS_HANGUL_ENGINE_H_
#define __Q_IBUS_HANGUL_ENGINE_H_
 
#include <hangul-1.0/hangul.h>
#include <qibus.h>
 
using namespace IBus;
 
class DemoEngine : public Engine
{
    Q_OBJECT
 
public :
    DemoEngine () {}
    Q_INVOKABLE DemoEngine (const QString &name): Engine(name) {}
 
    virtual ~DemoEngine () {}
 
private :
    Q_INVOKABLE bool ProcessKeyEvent(uint keyVal, uint keyCode, uint modifiers);
 
private :
 
    LookupTablePointer  m_table;
    PropertyPointer     m_prop;
    PropListPointer     m_propList;
};
 
#endif
