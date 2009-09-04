#include <QCoreApplication>
#include "qibusdemoengine.h"
 
using namespace IBus;
 
int main (int argc, char **argv)
{
    QCoreApplication app (argc, argv);
 
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
 
    Bus bus;
    if ( !bus.isConnected() ) {
        qDebug () << "bus is not connected!";
        return -1;
    }
 
    EngineFactory factory(bus.getConnection());
    factory.addMetaObject("hangul", &(DemoEngine::staticMetaObject));

    bus.registerObject ("/org/freedesktop/IBus/Factory", &factory);
 
    if ( !bus.registerComponent(cmpt) ) {
        qDebug () << "registerComponent error!";
        return -1;
    }
    
    return QCoreApplication::exec ();
}
