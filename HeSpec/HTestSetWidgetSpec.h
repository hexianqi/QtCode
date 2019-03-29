#ifndef HTESTSETWIDGETSPEC_H
#define HTESTSETWIDGETSPEC_H

#include "HeGui/HAbstractTestSetWidget.h"

HE_GUI_USE_NAMESPACE

namespace Ui {
class HTestSetWidgetSpec;
}

class HTestSetWidgetSpecPrivate;

class HTestSetWidgetSpec : public HAbstractTestSetWidget
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HTestSetWidgetSpec)

public:
    explicit HTestSetWidgetSpec(QWidget *parent = nullptr);
    ~HTestSetWidgetSpec() override;

public:
    QString typeName() override;
    void handleAction(HActionType action) override;
    bool setTestState(bool b) override;
    bool setTestMode(int value) override;

protected slots:
    void setIntegralTime(double value);
    void setIntegralTimeAuto(bool b);
    void on_checkBox_01_clicked(bool b);
    void on_checkBox_02_clicked(bool b);
    void on_radioButton_01_clicked();
    void on_radioButton_02_clicked();

private:
    void init();

private:
    Ui::HTestSetWidgetSpec *ui;
};

#endif // HTESTSETWIDGETSPEC_H
