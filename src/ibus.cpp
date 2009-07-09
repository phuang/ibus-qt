#include <Qt>
#include <QtDebug>
#include <QDBusMessage>
#include <QCoreApplication>
#include <QList>
#include "qibusserializable.h"
#include "qibusconnection.h"
#include "qibusbus.h"

class App : QCoreApplication {
public:
    App (int &argc, char **argv ) : QCoreApplication (argc, argv) {
    }
};

int main (int argc, char **argv)
{
    App app(argc, argv);

    QIBusConnection connection (QString ("unix:path=/tmp/ibus-phuang/ibus-unix-0"));

    QIBusBus bus (QString ("org.freedesktop.IBus"),
                  QString ("/org/freedesktop/IBus"),
                  connection.getConnection ());


    QDBusArgument arg;
    QIBusSerializable *obj1, *obj2;

    obj1 = new QIBusSerializable ();
    QIBusSerializable::serializeObject (obj1, arg);
    delete obj1;

    QDBusPendingReply<QDBusVariant> ret = bus.Ping (QDBusVariant (QVariant::fromValue (arg)));

    QDBusArgument argout = ret.argumentAt<0>().variant().value<QDBusArgument>();

    QIBusSerializable::deserializeObject (obj2, argout);

    return 0;
}
