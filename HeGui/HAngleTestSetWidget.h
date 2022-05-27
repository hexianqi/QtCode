#pragma once

#include "HAbstractTestSetWidget.h"

namespace Ui {
class HAngleTestSetWidget;
}

HE_BEGIN_NAMESPACE

class HAngleTestSetWidgetPrivate;

class HAngleTestSetWidget : public HAbstractTestSetWidget
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HAngleTestSetWidget)

public:
    explicit HAngleTestSetWidget(QWidget *parent = nullptr);
    ~HAngleTestSetWidget() override;

public:
    QString typeName() override;

public:
    QVariant handleOperation(QString type, QVariant value = QVariant()) override;
    void handleAction(HActionType action) override;
    bool setTestState(bool b) override;

protected slots:
    void on_doubleSpinBox_2_valueChanged(double value);
    void on_doubleSpinBox_3_valueChanged(double value);
    void on_comboBox_2_currentIndexChanged(int value);
    void on_comboBox_3_currentIndexChanged(int value);

protected:
    bool adjustLuminousGears();
    void updateUI();

private:
    void init();

private:
    Ui::HAngleTestSetWidget *ui;
};

HE_END_NAMESPACE
