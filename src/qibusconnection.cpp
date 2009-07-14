#include "qibusconnection.h"

namespace IBus {

Connection::Connection (const QString &address)
    : connection (QDBusConnection::connectToBus (address, QString ("IBus")))
{
}

Connection::~Connection ()
{
}

};
