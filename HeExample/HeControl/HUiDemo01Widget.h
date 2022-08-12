/***************************************************************************************************
**      2022-08-11  HUiDemo01Widget
***************************************************************************************************/

#pragma once

#include "HNamespace.h"
#include <QtWidgets/QWidget>

namespace Ui {
class HUiDemo01Widget;
}

HE_BEGIN_NAMESPACE

class HUiDemo01WidgetPrivate;

class HUiDemo01Widget : public QWidget
{
    Q_OBJECT

public:
    explicit HUiDemo01Widget(QWidget *parent = nullptr);
    ~HUiDemo01Widget() override;

protected slots:
    void initForm();
    void initStyle();
    void initLeftMain();
    void initLeftConfig();
    void leftMainClick();
    void leftConfigClick();
    void on_btnMain_clicked();
    void on_btnConfig_clicked();
    void on_btnData_clicked();
    void on_btnHelp_clicked();
    void on_btnExit_clicked();
    void on_btnMin_clicked();
    void on_btnMax_clicked();
    void on_btnClose_clicked();

protected:
    bool eventFilter(QObject *watched, QEvent *event) override;

protected:
    QScopedPointer<HUiDemo01WidgetPrivate> d_ptr;

private:
    Ui::HUiDemo01Widget *ui;
};

HE_END_NAMESPACE

