#include <Qt>
#include <QtDebug>
#include <QDBusMessage>
#include <QCoreApplication>
#include <QDBusArgument>
#include <QList>
#include <QMetaType>
#include "qibusserializable.h"
#include "qibusconnection.h"
#include "qibusbus.h"

class App : QCoreApplication {
public:
    App (int &argc, char **argv ) : QCoreApplication (argc, argv) {
    }
};

class MyStructure {
    friend QDBusArgument &operator<< (QDBusArgument &argument, const MyStructure &m);
    friend const QDBusArgument &operator>> (const QDBusArgument &argument, MyStructure &m);

public:
    MyStructure ()  { }
    MyStructure (const QString &name, int value) : name (name), value (value) { }

    QString name;
    int value;
};

Q_DECLARE_METATYPE(MyStructure)

QDBusArgument &operator<< (QDBusArgument &argument, const MyStructure &m)
{
    qDebug ("<<");
    argument.beginStructure();
    argument << m.name << m.value;
    argument.endStructure();
    return argument;
}

const QDBusArgument &operator>> (const QDBusArgument &argument, MyStructure &m)
{
    qDebug (">>");
    argument.beginStructure();
    argument >> m.name >> m.value;
    argument.endStructure();
    return argument;
}


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
    
    qDBusRegisterMetaType<MyStructure>();
    MyStructure s (QString ("Hello"), 99);


    ret = bus.Ping (QDBusVariant(QVariant::fromValue (s)));
    
    MyStructure ss (QString ("zzz"), 99);
    ret.reply() >> ss;

    return 0;
}
