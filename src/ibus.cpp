#include <Qt>
#include "qibusserializable.h"

int main()
{
    QIBusSerializable *obj = new QIBusSerializable ();
    QDBusArgument arg;

    obj->serialize(arg);
    delete obj;
    
    obj = (QIBusSerializable *) QIBusSerializable::staticMetaObject.newInstance();
    obj->deserialize(arg);

    delete obj;
    return 0;
}
