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
    QList<QMenu *> menus() override;
    QList<QToolBar *> toolBars() override;

public:
    void start() override;
    void stop() override;

protected:
    HAbstractTestWidget(HAbstractTestWidgetPrivate &p, QWidget *parent = nullptr);

protected:
    void closeEvent(QCloseEvent *) override;
    virtual bool setTest(bool b) = 0;
    virtual void handleAction(HActionType action) = 0;

protected:
    QScopedPointer<HAbstractTestWidgetPrivate> d_ptr;
};

HE_GUI_END_NAMESPACE

#endif // HABSTRACTTESTWIDGET_H
