#include "qibusdemoengine.h"
#include <QDebug>

DemoEngine::DemoEngine (const QString &name)
: Engine(name)
{
    m_lookupTable = NULL;
    m_candicate = NULL;
}

DemoEngine::~DemoEngine () {}

void
DemoEngine::closeLookupTable ()
{
    m_lookupTable->clean ();
    hidePreeditText ();
    hideAuxiliaryText ();
    hideLookupTable ();
}

// follows are virtual functions
void
DemoEngine::propertyActivate (const QString &prop_name, int prop_state)
{
    qDebug () << "Activate";
    TextPointer tooltip = new Text ("toggle to english");
    TextPointer label = new Text ("setup");
    PropertyPointer prop = new Property ("setup",
                                "/home/doyle/IME/ibus-pinyin/icons/english.svg",
                                label,
                                tooltip,
                                true,
                                true,
                                TypeNormal,
                                0,
                                NULL);

    updateProperty (prop);
}

bool
DemoEngine::processKeyEvent (uint keyval, uint keycode, uint modifiers)
{
    if (modifiers & ReleaseMask) {
        return false;
    }

    uint indexOfcandidate = 0;
    
    TextPointer tooltip = NULL;
    TextPointer label = NULL;
    PropListPointer props = NULL;
    PropertyPointer prop = NULL;

    TextPointer attributeText = NULL;

    switch (keyval) {
        case Key_a :
        /*
            attributeText = new Text ("Apple");
            attributeText->appendAttribute (Attribute::TypeUnderline, Attribute::UnderlineLow, 0, -1);
            attributeText->appendAttribute (Attribute::TypeForeground, 0xff0000, 0, -1);
            updatePreeditText (attributeText, 0, TRUE);
            break;
        */

        case Key_b :
            attributeText = new Text ("Banana");
            attributeText->appendAttribute (Attribute::TypeUnderline, Attribute::UnderlineSingle, 0, -1);
            attributeText->appendAttribute (Attribute::TypeBackground, 0xff0000, 0, -1);
            updatePreeditText (attributeText, 0, TRUE);
            break;

        case Key_c :
            updateAuxiliaryText (new Text ("CCCCC"), TRUE);
            break;

        case Key_p :
            label = new Text ("setup");
            tooltip = new Text ("toggle to english");
            prop = new Property ("setup",
                                "/home/doyle/IME/ibus-pinyin/icons/chinese.svg",
                                label,
                                tooltip,
                                true,
                                true,
                                TypeNormal,
                                0,
                                NULL);
            props = new PropList ();
            props->appendProperty (prop);
            registerProperties (props);
            break;

        case Key_d :
        {
            m_lookupTable = new LookupTable (true, true, 5, 0);
            m_lookupTable->appendLabel (new Text ("1"));
            m_lookupTable->appendLabel (new Text ("2"));
            m_lookupTable->appendLabel (new Text ("3"));
            m_lookupTable->appendLabel (new Text ("4"));
            m_lookupTable->appendLabel (new Text ("5"));
            attributeText = new Text("ibus");
            attributeText->appendAttribute (Attribute::TypeForeground, 0xff0000, 0, -1);
            m_lookupTable->appendCandidate (attributeText);
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
            commitText (new Text("commitText"));
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

        case Key_s :
            showLookupTable ();
            break;

        case Key_g :
            hideLookupTable ();
            break;

        case Key_i :
            hidePreeditText ();
            break;

        case Key_m :
            hideAuxiliaryText ();
            break;

        case Key_n :
            break;

        case Key_Escape :
            closeLookupTable ();

        case Key_1 :
        case Key_2 :
        case Key_3 :
        case Key_4 :
        case Key_5 :
        case Key_6 :
        case Key_7 :
        case Key_8 :
        case Key_9 :
            indexOfcandidate = keyval - 49;
            if ( m_lookupTable->candidate(0) != NULL ) {
                if ( (m_candicate = m_lookupTable->candidate(indexOfcandidate)) != NULL ) {
                    commitText (m_candicate);
                    closeLookupTable ();
                }

                break;
            }

            commitText (new Text (static_cast<QChar>(keyval)));
            break;

        default:
            qDebug () << "Unknown key input!";
            return false;
    }

    return true;
}

