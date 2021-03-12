/***************************************************************************************************
**      2019-06-04  HControlTester 测试类。
***************************************************************************************************/

#pragma once

#include "IControlFactory.h"

HE_CONTROL_BEGIN_NAMESPACE

class HControlFactoryPrivate;

class HE_CONTROL_EXPORT HControlFactory : public QObject, public IControlFactory
{
    Q_OBJECT

public:
    explicit HControlFactory(QObject *parent = nullptr);
    ~HControlFactory() override;

public:
    void initialize(QVariantMap param) override;
    QString typeName() override;

public:
    QStringList supportedWidgets() override;
    QStringList supportedEventFilters() override;
    QWidget *createWidget(const QString &type, QWidget *parent = nullptr) override;
    IEventFilter *createEventFilter(const QString &type, QVariantMap param = QVariantMap()) override;

protected:
    QScopedPointer<HControlFactoryPrivate> d_ptr;

private:
    void registerClass();
};

HE_CONTROL_END_NAMESPACE
