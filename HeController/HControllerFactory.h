#ifndef HCONTROLLERFACTORY_H
#define HCONTROLLERFACTORY_H

#include "IControllerFactory.h"

HE_CONTROLLER_BEGIN_NAMESPACE

class HControllerFactoryPrivate;

class HE_CONTROLLER_EXPORT HControllerFactory : public IControllerFactory
{
public:
    explicit HControllerFactory();
    ~HControllerFactory();

public:
    virtual void initialize(QVariantMap param) override;
    virtual IThreadCollection *createThreadCollection(QString type, QVariantMap param = QVariantMap()) override;

protected:
    HControllerFactory(HControllerFactoryPrivate &p);

protected:
    QScopedPointer<HControllerFactoryPrivate> d_ptr;
};

HE_CONTROLLER_END_NAMESPACE

#endif // HCONTROLLERFACTORY_H
