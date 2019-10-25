#ifndef HELECCALIBRATEITEM1WIDGET_H
#define HELECCALIBRATEITEM1WIDGET_H

#include "HElecCalibrateItemWidget.h"

namespace Ui {
class HElecCalibrateItem1Widget;
}

HE_GUI_BEGIN_NAMESPACE

class HElecCalibrateItem1WidgetPrivate;

class HElecCalibrateItem1Widget : public HElecCalibrateItemWidget
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HElecCalibrateItem1Widget)

public:
    explicit HElecCalibrateItem1Widget(QWidget *parent = nullptr);
    ~HElecCalibrateItem1Widget() override;

public:
    void showData() override;
    void saveData() override;

protected slots:
    void on_pushButton_1_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();

private:
    Ui::HElecCalibrateItem1Widget *ui;
};

HE_GUI_END_NAMESPACE

#endif // HELECCALIBRATEITEM1WIDGET_H
