#ifndef __Q_IBUS_BUS_H_
#define __Q_IBUS_BUS_H_

#include <QFileSystemWatcher>
#include <QDBusConnection>
#include "qibusobject.h"
#include "qibusserializable.h"
#include "qibusenginedesc.h"
#include "qibuscomponent.h"
#include "qibusengine.h"

class QDBusConnection;
class IBusProxy;
class DBusProxy;

namespace IBus {

class Bus;
typedef Pointer<Bus> BusPointer;

class Bus : public Object
{
    Q_OBJECT;

protected:

public:
    Bus (void);
    ~Bus (void);
    bool isConnected (void);
    const QDBusConnection &getConnection (void);

    /* org.freedesktop.DBus methods */
    QString hello (void);
    void addMatch (const QString &rule);
    void removeMatch (const QString &rule);
    QString getId (void);
    QString getNameOwner (const QString &name);
    QStringList listNames (void);
    bool nameHasOwner (const QString &name);
    uint requestName (const QString &name, uint flag);
    uint releaseName (const QString &name);

    /* org.freedesktop.IBus methods */
    QString createInputContext (const QString &name);
    bool registerComponent (const ComponentPointer &component);
    bool registerObject (const QString &path, QObject *obj);

    QList<EngineDescPointer> listEngines (void);
    QList<EngineDescPointer> listActiveEngines (void);
    bool exit (bool restart = false);
    SerializablePointer ping (const SerializablePointer &data);

private:
    bool open (void);
    void reset (void);
    QString getSocketPath (void);
    QString getAddress (void);

signals:
    /**
     * @brief Emited when bus is disconnected from ibus daemon.
     */
    void disconnected (void);

    /**
     * @brief Emited when bus is connected to ibus daemon.
     */
    void connected (void);

private slots:
    void slotAddressChanged (const QString &path);
    void slotIBusDisconnected (void);

private:
    QFileSystemWatcher m_watcher;
    QDBusConnection *m_connection;
    DBusProxy *m_dbus;
    IBusProxy *m_ibus;
};

};

#endif
