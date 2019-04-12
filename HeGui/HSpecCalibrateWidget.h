/***************************************************************************************************
**      2019-04-11  HSpecCalibrateWidget 光谱校准窗体。
***************************************************************************************************/

#ifndef HSPECCALIBRATEWIDGET_H
#define HSPECCALIBRATEWIDGET_H

#include "HAbstractTestWidget.h"
#include "HeData/HDataGlobal.h"

namespace Ui {
class HSpecCalibrateWidget;
}

HE_DATA_BEGIN_NAMESPACE
class ISpecCalibrate;
HE_DATA_END_NAMESPACE
HE_DATA_USE_NAMESPACE

HE_GUI_BEGIN_NAMESPACE

class ITestSetWidget;
class HSpecCalibrateWidgetPrivate;

class HE_GUI_EXPORT HSpecCalibrateWidget : public HAbstractTestWidget
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HSpecCalibrateWidget)

public:
    explicit HSpecCalibrateWidget(QWidget *parent = nullptr);
    ~HSpecCalibrateWidget();

public:
    QString typeName() override;

public:
    void setSpecCalibrate(ISpecCalibrate *);
    void setTestSetWidget(ITestSetWidget *);

protected:
    bool setTest(bool b) override;
    void handleAction(HActionType action) override;

protected slots:
    void handleTestStateChanged(bool b);
    void handleTestModeChanged(int value);
    void handleTestFitStateChanged(bool b);
    void on_tabWidget_1_currentChanged(int index);
    void on_pushButton_1_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();

protected:
    void refreshCcdView(int i);
    void refreshSpecWidget();

private:
    void init();

private:
    Ui::HSpecCalibrateWidget *ui;
};

HE_GUI_END_NAMESPACE

#endif // HSPECCALIBRATEWIDGET_H
