#include <Qt>
#include "qibusserializable.h"

int main()
{
    QDBusArgument arg;
    QIBusSerializable *obj;

    obj = new QIBusSerializable ();
    obj->serialize(arg);
    delete obj;
    
    obj = QIBusSerializable::newFromName ("IBusSerializable");
    obj->deserialize(arg);
    delete obj;

    obj = QIBusSerializable::newFromName ("IBusText");
    obj->deserialize(arg);
    delete obj;

    return 0;
}
