#include "qibusdemoengine.h"
#include <QDebug>

DemoEngine::DemoEngine (const QString &name)
: Engine(name)
{}

DemoEngine::~DemoEngine ()
{}

void
DemoEngine::initialize ()
{
    TextPointer lable = new Text("Setup");
    TextPointer tooltip = new Text("configuration demo engine");

    PropertyPointer prop = new Property("setup",
                                        "gtk-preference",
                                        lable,
                                        tooltip,
                                        true,
                                        true,
                                        TypeNormal,
                                        0,
                                        NULL);

    m_table = new LookupTable(5, 0, true, false);
    m_propList = new PropList();
    m_propList->appendProperty(prop);
}

void
DemoEngine::clearup () {}

// call the corresponding function in base class--Engine
void
DemoEngine::UpdatePreeditText ()
{
    if ( m_context.size() > 0 ) {
        TextPointer text = new Text(m_context);
        updatePreeditText(text, m_context.size(), true);
        return ;
    }

    TextPointer text = new Text();
    updatePreeditText(text, 0, false);
}

void
DemoEngine::UpdateAuxiliaryText ()
{
    uint cursorPos = m_table->getCursorPos();
}

void
DemoEngine::UpdateLookupTable ()
{
    updateLookupTable(m_table, true);
}

void
DemoEngine::CommitCurrentCandidate ()
{}

void
DemoEngine::CloseLookupTable ()
{
    hideLookupTable();
    hideAuxiliaryText();
}

// follows are virtual functions
bool
DemoEngine::processKeyEvent (uint keyval, uint keycode, uint modifiers)
{
    if ( keyval == Key_Shift_L || keyval == Key_Shift_R ) {
        return false;
    }

    qDebug () << "Process Key Event";
    return true;
}
