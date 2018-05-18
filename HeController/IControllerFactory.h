#ifndef ICONTROLLERFACTORY_H
#define ICONTROLLERFACTORY_H

#include "HControllerGlobal.h"
#include "HeCore/IInitializeable.h"

HE_CORE_USE_NAMESPACE

HE_CONTROLLER_BEGIN_NAMESPACE

class IThreadCollection;

class HE_CONTROLLER_EXPORT IControllerFactory : public IInitializeable
{
public:
    // 创建线程集合
    virtual IThreadCollection *createThreadCollection(QString type, QVariantMap param = QVariantMap()) = 0;
};

HE_CONTROLLER_END_NAMESPACE

#endif // ICONTROLLERFACTORY_H
