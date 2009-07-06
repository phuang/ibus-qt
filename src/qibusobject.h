#ifndef __Q_IBUS_OBJECT_H__
#define __Q_IBUS_OBJECT_H__

#include <QObject>

class QIBusObject : public QObject
{
    Q_OBJECT

public:
    Q_INVOKABLE QIBusObject ();
};

#endif
