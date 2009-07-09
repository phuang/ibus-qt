#include "qibusconnection.h"

QIBusConnection::QIBusConnection (const QString &address)
    : connection (QDBusConnection::connectToBus (address, QString ("IBus")))
{
}

QIBusConnection::~QIBusConnection ()
{
}
