#ifndef __Q_IBUS_ENGINE_DESC_H_
#define __Q_IBUS_ENGINE_DESC_H_

#include "qibusserializable.h"

namespace IBus {

class EngineDesc;
typedef Pointer<EngineDesc> EngineDescPointer;

class EngineDesc : public Serializable
{
    Q_OBJECT;

protected:

public:
    EngineDesc (void);
    EngineDesc (const QString &text) : m_text (text) {}

public:
    virtual bool serialize (QDBusArgument &argument) const;
    virtual bool deserialize (const QDBusArgument &argument);

private:
    QString m_text;

    IBUS_SERIALIZABLE
};

};

#endif
