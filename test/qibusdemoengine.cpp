#include "qibusdemoengine.h"
#include <QDebug>

DemoEngine::DemoEngine (const QString &name)
: Engine(name)
{
    m_lookupTable = NULL;
}

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

    m_lookupTable = new LookupTable(5, 0, true, false);
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
{}

void
DemoEngine::UpdateLookupTable ()
{
    updateLookupTable(m_lookupTable, true);
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
    if (modifiers & ReleaseMask) {
        return false;
    }
    
    TextPointer tooltip = new Text ("configuration demo engine");
    TextPointer lable = new Text("Setup");
    PropertyPointer prop = NULL;

    switch (keyval) {
        case Key_a :
            updatePreeditText (new Text ("Apple"), 0, TRUE);
            break;

        case Key_b :
            updatePreeditText (new Text ("Banana"), 0, TRUE);
            break;

        case Key_c :
            updateAuxiliaryText (new Text ("CCCCC"), TRUE);
            break;

        case Key_p :
            prop = new Property("setup",
                                "gtk-preference",
                                                lable,
                                                tooltip,
                                                // new ("demo engine"), // lable,
                                                // new ("setup"), // tooltip,
                                                true,
                                                true,
                                                TypeNormal,
                                                0,
                                                NULL);

            updateProperty (prop);
            break;

        case Key_d :
        {
            m_lookupTable = new LookupTable (true, true, 5, 0);
            m_lookupTable->appendLabel (new Text ("1"));
            m_lookupTable->appendLabel (new Text ("2"));
            m_lookupTable->appendLabel (new Text ("3"));
            m_lookupTable->appendLabel (new Text ("4"));
            m_lookupTable->appendLabel (new Text ("5"));
            m_lookupTable->appendCandidate (new Text ("ibus"));
            m_lookupTable->appendCandidate (new Text ("wubi"));
            m_lookupTable->appendCandidate (new Text ("chewing"));
            m_lookupTable->appendCandidate (new Text ("IBM"));
            m_lookupTable->appendCandidate (new Text ("Yahoo"));
            m_lookupTable->appendCandidate (new Text ("dbus"));
            m_lookupTable->appendCandidate (new Text ("redhat"));
            m_lookupTable->appendCandidate (new Text ("bupt"));
            m_lookupTable->appendCandidate (new Text ("smth"));
            m_lookupTable->appendCandidate (new Text ("sogou"));
            m_lookupTable->appendCandidate (new Text ("google"));
            m_lookupTable->appendCandidate (new Text ("ziguang"));
            updateLookupTable (m_lookupTable, true);
            break;
        }

        case Key_e :
            commitText (new Text(Key_e));
            break;

        case Key_j :
            PageDownLookupTable ();
            break;

        case Key_k :
            PageUpLookupTable ();
            break;

        case Key_h :
            CursorUpLookupTable ();
            break;

        case Key_l :
            CursorDownLookupTable ();
            break;

        case Key_Up :
            m_lookupTable->cursorUp();
            updateLookupTable (m_lookupTable, true);
            break;

        case Key_Down :
            m_lookupTable->cursorDown();
            updateLookupTable (m_lookupTable, true);
            break;

        case Key_Left :
            m_lookupTable->cursorUp();
            updateLookupTable (m_lookupTable, true);
            break;

        case Key_Right :
            m_lookupTable->cursorDown();
            updateLookupTable (m_lookupTable, true);
            break;

        case Key_Page_Up :
            m_lookupTable->pageUp ();
            updateLookupTable (m_lookupTable, true);
            break;

        case Key_Page_Down :
            m_lookupTable->pageDown ();
            updateLookupTable (m_lookupTable, true);
            break;

        case Key_g :
            hideLookupTable ();
            break;

        case Key_s :
            showLookupTable ();
            break;

        default:
            hidePreeditText ();
            return false;
    }

    return true;
}

