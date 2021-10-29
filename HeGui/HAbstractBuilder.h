/***************************************************************************************************
**      2019-03-01  HAbstractBuilder 抽象创建者类。
***************************************************************************************************/

#pragma once

#include "IBuilder.h"

HE_GUI_BEGIN_NAMESPACE

class IMainWindow;
class HAbstractBuilderPrivate;

class HE_GUI_EXPORT HAbstractBuilder : public QObject, public IBuilder
{
    Q_OBJECT

public:
    explicit HAbstractBuilder(QObject *parent = nullptr);

public:
    void initialize(QVariantMap param) override;

public:
    void buildAll() override;

protected:
    HAbstractBuilder(HAbstractBuilderPrivate &p, QObject *parent = nullptr);

protected:
    virtual void readSettings();
    virtual void writeSettings();
    virtual void buildFactory();
    virtual void buildConfigManage() = 0;
    virtual void buildTestData() = 0;
    virtual void buildTemplate() = 0;
    virtual void buildDevice() = 0;
    virtual void buildThread() = 0;
    virtual void buildModel() = 0;
    virtual void buildMemento() = 0;
    virtual void buildDatabase() = 0;
    virtual void buildMenu() = 0;
    virtual void buildTestWidget() = 0;

protected:
    QString deployItem(const QString &key);

protected:
    QScopedPointer<HAbstractBuilderPrivate> d_ptr;
};

HE_GUI_END_NAMESPACE
