/***************************************************************************************************
**      2019-06-13  HControlWidget 控件测试窗体。
***************************************************************************************************/

#ifndef HCONTROLWIDGET_H
#define HCONTROLWIDGET_H

#include "HControlGlobal.h"
#include <QtWidgets/QWidget>

namespace Ui {
class HControlWidget;
}

HE_CONTROL_BEGIN_NAMESPACE

class HControlWidgetPrivate;

class HE_CONTROL_EXPORT HControlWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HControlWidget(QWidget *parent = nullptr);
    ~HControlWidget();

private slots:
    void on_pushButton_clicked();

private:
    void init();

private:
    Ui::HControlWidget *ui;
    QScopedPointer<HControlWidgetPrivate> d_ptr;
};

HE_CONTROL_END_NAMESPACE

#endif // HCONTROLWIDGET_H
