#ifndef __Q_IBUS_BUS_H_
#define __Q_IBUS_BUS_H_

#include "qibusobject.h"

class QFileSystemWatcher;
class QDBusConnection;
class IBusAdaptor;
class DBusAdaptor;

namespace IBus {

class Bus : public Object
{
    Q_OBJECT;

protected:

public:
    Bus (void);
    ~Bus (void);
    bool connect (void);
    bool isConnected (void);

private:
    void init (void);
    void reset (void);
    QString getSocketPath (void);
    QString getAddress (void);

private slots:
    void addressChanged (const QString &path);

private:
    QFileSystemWatcher *m_watcher;
    QDBusConnection *m_connection;
    IBusAdaptor *m_dbus;
    DBusAdaptor *m_ibus;
};

};

#endif
