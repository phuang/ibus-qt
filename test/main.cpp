#include <QCoreApplication>
#include "qibusdemoengine.h"
 
using namespace IBus;
 
int main (int argc, char **argv)
{
    QCoreApplication app (argc, argv);
 
#if 0

    ComponentPointer cmpt = new Component;
    if ( !newComponentFromFile(*cmpt, "component/m17n.xml") ) {
        qDebug () << "main::newComponentFromFile error!";
        return -1;
    }

    Bus bus;
    if ( !bus.isConnected() ) {
        qDebug () << "main::bus is not connected!";
        return -1;
    }
 
    EngineFactory *engineFactory = EngineFactory::getEngineFactory(bus.getConnection());
    engineFactory->addMetaObject("kn:inscript", &(DemoEngine::staticMetaObject));

    if ( !bus.registerObject ("/org/freedesktop/IBus/Factory", engineFactory) ) {
        qDebug () << "main::registerObject error!";
        return -1;
    }
 
    if ( !bus.registerComponent(cmpt) ) {
        qDebug () << "main::registerComponent error!";
        return -1;
    }

#endif

#if 0
    ComponentPointer cmpt = new Component;
    if ( !newComponentFromFile(*cmpt, "component/hangul.xml") ) {
        qDebug () << "main::newComponentFromFile error!";
        return -1;
    }


    /*
    QString stream;
    cmpt->output(stream);
    qDebug () << stream;

    EngineDescPointer engine = (cmpt->engines())[0];
    QString str;
    engine->output(str);
    qDebug () << str;
    */

    Bus bus;
    if ( !bus.isConnected() ) {
        qDebug () << "main::bus is not connected!";
        return -1;
    }
 
    EngineFactory *engineFactory = EngineFactory::getEngineFactory(bus.getConnection());
    engineFactory->addMetaObject("hangul", &(DemoEngine::staticMetaObject));

    if ( !bus.registerObject ("/org/freedesktop/IBus/Factory", engineFactory) ) {
        qDebug () << "main::registerObject error!";
        return -1;
    }
 
    if ( !bus.registerComponent(cmpt) ) {
        qDebug () << "main::registerComponent error!";
        return -1;
    }

#endif

#if 1
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

/*
    QString stream;
    cmpt->output(stream);
    qDebug () << stream;

    EngineDescPointer eng = (cmpt->engines())[0];
    QString str;
    eng->output(str);
    qDebug () << str;
*/

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

#endif
    
    return QCoreApplication::exec ();
}
