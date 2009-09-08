#include <QCoreApplication>
#include "qibusdemoengine.h"
 
using namespace IBus;
 
int main (int argc, char **argv)
{
    QCoreApplication app (argc, argv);
#if 0
    ComponentPointer cmpt = new Component();
    cmpt->newComponentFromFile("hangul.xml");

#else
    ComponentPointer cmpt = new Component("org.freedesktop.IBus.Qt.DemoEngine",
                    "Qt Demo Engine",
                    "0.1.0",
                    "GPL",
                    "Peng Huang <shawn.p.huang@gmail.com>",
                    "http://code.google.com/p/ibus/",
                    "",
                    "ibus-qt");
 
    EngineDescPointer engine = new EngineDesc("qtdemo",
                    "Qt Demo Input Method",
                    "Qt Demo Input Method",
                    "en",
                    "GPL",
                    "Peng Huang <shawn.p.huang@gmail.com>",
                    "ibus",
                    "us");

    cmpt->addEngine(engine);

#endif
 
    Bus bus;
    if ( !bus.isConnected() ) {
        qDebug () << "bus is not connected!";
        return -1;
    }
 
    EngineFactory *engineFactory = EngineFactory::getEngineFactory(bus.getConnection());
    engineFactory->addMetaObject("qtdemo", &(DemoEngine::staticMetaObject));

    bus.registerObject ("/org/freedesktop/IBus/Factory", engineFactory);
 
    if ( !bus.registerComponent(cmpt) ) {
        qDebug () << "registerComponent error!";
        return -1;
    }
    
    return QCoreApplication::exec ();
}
