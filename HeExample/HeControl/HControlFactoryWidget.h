/***************************************************************************************************
**      2019-06-13  HControlWidget 控件测试窗体。
***************************************************************************************************/

#pragma once

#include "HNamespace.h"
#include <QtWidgets/QWidget>

namespace Ui {
class HControlFactoryWidget;
}

HE_BEGIN_NAMESPACE

class HControlFactoryWidgetPrivate;

class HControlFactoryWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HControlFactoryWidget(QWidget *parent = nullptr);
    ~HControlFactoryWidget();

private slots:
    void on_pushButton_clicked();

private:
    void init();

private:
    Ui::HControlFactoryWidget *ui;
    QScopedPointer<HControlFactoryWidgetPrivate> d_ptr;
};

HE_END_NAMESPACE
