#include "qibusconnection.h"

namespace IBus {

Connection::Connection (const QString &address)
    : m_connection (QDBusConnection::connectToBus (address, QString ("IBus")))
{
}

Connection::~Connection ()
{
}

};
