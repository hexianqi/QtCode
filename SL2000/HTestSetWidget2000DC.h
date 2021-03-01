#ifndef HTESTSETWIDGET2000DC_H
#define HTESTSETWIDGET2000DC_H

#include "HeGui/HAbstractTestSetWidget.h"

HE_GUI_USE_NAMESPACE

namespace Ui {
class HTestSetWidget2000DC;
}

class HTestSetWidget2000DCPrivate;

class HTestSetWidget2000DC : public HAbstractTestSetWidget
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HTestSetWidget2000DC)

public:
    explicit HTestSetWidget2000DC(QWidget *parent = nullptr);
    ~HTestSetWidget2000DC() override;

public:
    void initialize(QVariantMap param) override;
    QString typeName() override;

public:
    QVariant handleOperation(QString type, QVariant value = QVariant()) override;
    void handleAction(HActionType action) override;
    bool setTestState(bool b) override;

protected slots:
    void on_doubleSpinBox_1_valueChanged(double value);
    void on_doubleSpinBox_2_valueChanged(double value);
    void on_doubleSpinBox_3_valueChanged(double value);
    void on_doubleSpinBox_4_valueChanged(double value);
    void on_checkBox_1_clicked(bool b);
    void on_checkBox_2_clicked(bool b);
    void on_comboBox_1_currentIndexChanged(int value);
    void on_comboBox_2_currentIndexChanged(int value);
    void on_comboBox_3_currentIndexChanged(int value);

protected:
    bool adjustIntegralTime();
    bool adjustLuminousGears();

private:
    void init();

private:
    Ui::HTestSetWidget2000DC *ui;
};

#endif // HTESTSETWIDGET2000DC_H
