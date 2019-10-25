/***************************************************************************************************
**      2018-06-19  HControllerFactory 控制器工厂类。
***************************************************************************************************/

#ifndef HCONTROLLERFACTORY_H
#define HCONTROLLERFACTORY_H

#include "IControllerFactory.h"

HE_CONTROLLER_BEGIN_NAMESPACE

class HControllerFactoryPrivate;

class HE_CONTROLLER_EXPORT HControllerFactory : public QObject, public IControllerFactory
{
    Q_OBJECT

public:
    explicit HControllerFactory(QObject *parent = nullptr);
    ~HControllerFactory() override;

public:
    void initialize(QVariantMap param) override;
    QString typeName() override;

public:
    IThread *createThread(QString type, QVariantMap param) override;
    IThreadCollection *createThreadCollection(QString type, QVariantMap param = QVariantMap()) override;
    IModel *createModel(QString type, QVariantMap param = QVariantMap()) override;
    IActionStrategy *createStrategy(QString type, QVariantMap param = QVariantMap()) override;

protected:
    HControllerFactory(HControllerFactoryPrivate &p, QObject *parent = nullptr);

protected:
    QScopedPointer<HControllerFactoryPrivate> d_ptr;

private:
    void registerClass();
};

HE_CONTROLLER_END_NAMESPACE

#endif // HCONTROLLERFACTORY_H
