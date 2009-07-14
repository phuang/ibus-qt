#include <Qt>
#include <QtDebug>
#include <QDBusMessage>
#include <QCoreApplication>
#include <QDBusArgument>
#include <QList>
#include <QMetaType>
#include "qibusserializable.h"
#include "qibustext.h"
#include "qibusconnection.h"
#include "qibusbus.h"

using namespace IBus;

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
    qDBusRegisterMetaType<SerializablePointer>();

    QDBusArgument arg;

    {
        SerializablePointer p;
        p = new Serializable ();

        QVariant v = qVariantFromValue (p);
        QDBusVariant dv (v);
        SerializablePointer p1 = v.value<SerializablePointer>();
        arg << p;
    }


    App app(argc, argv);
    Connection connection (QString ("unix:path=/tmp/ibus-phuang/ibus-unix-0"));

    org::freedesktop::IBus bus (QString ("org.freedesktop.IBus"),
                  QString ("/org/freedesktop/IBus"),
                  connection.getConnection ());


    SerializablePointer p = /* (Serializable *) */ new Text ();
    QVariant v = qVariantFromValue (p);

    QDBusPendingReply<QDBusVariant> ret = bus.Ping (qDBusVariantFromSerializable (p));

    SerializablePointer p1 = qDBusVariantToSerializable (ret);

#if 0




    Serializable *obj1, *obj2;
    QDBusArgument arg;

    obj1 = new Serializable ();

    Serializable::serializeObject (obj1, arg);
    delete obj1;

    QVariant a = QVariant::fromValue(arg);


    QDBusArgument argout = ret.argumentAt<0>().variant().value<QDBusArgument>();

    Serializable::deserializeObject (obj2, argout);
#endif

    return 0;
}
