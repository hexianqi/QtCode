/***************************************************************************************************
**      2019-04-11  HSpecCalibrateWidget 光谱校准窗体。
***************************************************************************************************/

#pragma once

#include "HAbstractTestWidget.h"

namespace Ui {
class HSpecCalibrateWidget;
}

HE_BEGIN_NAMESPACE

class ISpecCalibrate;
class ITestSetWidget;
class HSpecCalibrateWidgetPrivate;

class HSpecCalibrateWidget : public HAbstractTestWidget
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HSpecCalibrateWidget)

public:
    explicit HSpecCalibrateWidget(QWidget *parent = nullptr);
    ~HSpecCalibrateWidget() override;

public:
    QString typeName() override;

public:
    void setCalibrate(ISpecCalibrate *);

protected:
    void handleAction(HActionType action) override;

protected slots:
    void handleStateChanged(bool b);
    void handleModeChanged(int value);
    void handleResultChanged();
    void handleFitStateChanged(bool b);
    void on_tabWidget_1_currentChanged(int index);
    void on_pushButton_1_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_6_clicked();

protected:
    void refreshCcdView();
    void refreshSpecWidget();

private:
    void init();

private:
    Ui::HSpecCalibrateWidget *ui;
};

HE_END_NAMESPACE
