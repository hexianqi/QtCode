/***************************************************************************************************
**      2019-03-21  HAbstractTestWidget 抽象测试窗体类。
***************************************************************************************************/

#ifndef HABSTRACTTESTWIDGET_H
#define HABSTRACTTESTWIDGET_H

#include "ITestWidget.h"
#include "HeCore/HActionType.h"

HE_GUI_BEGIN_NAMESPACE

class HAbstractTestWidgetPrivate;

class HE_GUI_EXPORT HAbstractTestWidget : public ITestWidget
{
    Q_OBJECT

public:
    explicit HAbstractTestWidget(QWidget *parent = nullptr);
    ~HAbstractTestWidget() override;

public:
    void initialize(QVariantMap param) override;

public:
    QVector<QMenu *> menus() override;
    QVector<QToolBar *> toolBars() override;

public:
    void start() override;
    void pause() override;

protected:
    HAbstractTestWidget(HAbstractTestWidgetPrivate &p, QWidget *parent = nullptr);

protected slots:
    virtual void actionDone(HActionType action) = 0;
    virtual bool setTesting(bool b);
    virtual void startTest();
    virtual void stopTest();

protected:
    QScopedPointer<HAbstractTestWidgetPrivate> d_ptr;
};

HE_GUI_END_NAMESPACE

#endif // HABSTRACTTESTWIDGET_H
