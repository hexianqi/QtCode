#pragma once

#include "HElecCalibrateItemWidget.h"

namespace Ui {
class HElecCalibrateItem2Widget;
}

HE_GUI_BEGIN_NAMESPACE

class HElecCalibrateItem2WidgetPrivate;

class HElecCalibrateItem2Widget : public HElecCalibrateItemWidget
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HElecCalibrateItem2Widget)

public:
    explicit HElecCalibrateItem2Widget(QWidget *parent = nullptr);
    ~HElecCalibrateItem2Widget() override;

public:
    void setLoop(bool b) override;
    void updateData(double value) override;
    void showData() override;
    void saveData() override;

protected slots:
    void on_pushButton_1_clicked();
    void on_checkBox_1_clicked(bool checked);

private:
    Ui::HElecCalibrateItem2Widget *ui;
};

HE_GUI_END_NAMESPACE
