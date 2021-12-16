/***************************************************************************************************
**      2019-03-21  HAbstractTestWidget 抽象测试窗体类。
***************************************************************************************************/

#pragma once

#include "ITestWidget.h"
#include "HeCore/HActionType.h"

HE_BEGIN_NAMESPACE

class HAbstractTestWidgetPrivate;

class HAbstractTestWidget : public ITestWidget
{
    Q_OBJECT

public:
    explicit HAbstractTestWidget(QWidget *parent = nullptr);
    ~HAbstractTestWidget() override;

public:
    void initialize(QVariantMap param = QVariantMap()) override;

public:
    QList<QMenu *> menus() override;
    QList<QToolBar *> toolBars() override;

public:
    void start() override;
    void stop() override;

protected:
    HAbstractTestWidget(HAbstractTestWidgetPrivate &p, QWidget *parent = nullptr);

protected slots:
    virtual void closeEvent(QCloseEvent *) override;
    virtual bool setTest(bool b);
    virtual void handleAction(HActionType action);

protected:
    QScopedPointer<HAbstractTestWidgetPrivate> d_ptr;
};

HE_END_NAMESPACE
