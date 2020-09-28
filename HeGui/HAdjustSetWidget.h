#pragma once

#include "HAbstractTestSetWidget.h"

namespace Ui {
class HAdjustSetWidget;
}

HE_GUI_BEGIN_NAMESPACE

class HAdjustSetWidgetPrivate;

class HAdjustSetWidget : public HAbstractTestSetWidget
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HAdjustSetWidget)

public:
    explicit HAdjustSetWidget(QWidget *parent = nullptr);
    ~HAdjustSetWidget() override;

public:
    void initialize(QVariantMap param) override;
    QString typeName() override;

public:
    void handleAction(HActionType action) override;
    bool setTestState(bool b) override;

protected slots:
    void on_doubleSpinBox_01_valueChanged(double value);
    void on_checkBox_01_clicked(bool b);
    void on_checkBox_02_clicked(bool b);

protected:
    bool adjustIntegralTime();

private:
    void init();

private:
    Ui::HAdjustSetWidget *ui;
};

HE_GUI_END_NAMESPACE
