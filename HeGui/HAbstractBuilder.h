/***************************************************************************************************
**      2019-03-01  HAbstractBuilder 抽象创建者类。
***************************************************************************************************/

#ifndef HABSTRACTBUILDER_H
#define HABSTRACTBUILDER_H

#include "IBuilder.h"
#include <QtCore/QObject>

HE_GUI_BEGIN_NAMESPACE

class IMainWindow;
class HAbstractBuilderPrivate;

class HE_GUI_EXPORT HAbstractBuilder : public QObject, public IBuilder
{
    Q_OBJECT

public:
    explicit HAbstractBuilder(IMainWindow *parent = nullptr);
    ~HAbstractBuilder() override;

public:
    void buildAll() override;

protected:
    HAbstractBuilder(HAbstractBuilderPrivate &p, IMainWindow *parent = nullptr);

protected:
    virtual void buildFactory();
    virtual void buildConfigManage() = 0;
    virtual void buildTestData() = 0;
    virtual void buildDevice() = 0;
    virtual void buildThread() = 0;
    virtual void buildModel() = 0;
    virtual void buildDatabase() = 0;
    virtual void buildTestWidget() = 0;

protected:
    QScopedPointer<HAbstractBuilderPrivate> d_ptr;
};

HE_GUI_END_NAMESPACE

#endif // HABSTRACTBUILDER_H
