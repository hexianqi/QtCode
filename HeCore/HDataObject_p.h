#ifndef HDATAOBJECT_P_H
#define HDATAOBJECT_P_H

#include "HCoreGlobal.h"
#include <QSharedData>

HE_CORE_BEGIN_NAMESPACE

class HE_CORE_EXPORT HDataObjectPrivate : public QSharedData
{
public:
    QString type;
};

HE_CORE_END_NAMESPACE

#endif // HDATAOBJECT_P_H
