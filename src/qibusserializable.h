#ifndef __Q_IBUS_SERIALIZABLE_H_
#define __Q_IBUS_SERIALIZABLE_H_

#include "qibusobject.h"
#include <QDBusArgument>

class QIBusSerializable : public QIBusObject
{

    Q_OBJECT

public:
    QIBusSerializable ();
    void setAttachment (const QString &key, QIBusSerializable *value);
    QIBusSerializable *getAttachment (const QString &key);

public:
    virtual bool serialize (QDBusArgument &argument);
    virtual bool deserialize (QDBusArgument &argument);
    virtual QIBusSerializable *copy ();

protected:


};

#endif
