/***************************************************************************************************
**      2019-06-12  HStyleWidget 样式窗体。
***************************************************************************************************/

#ifndef HSTYLEWIDGET_H
#define HSTYLEWIDGET_H

#include "HControlGlobal.h"
#include <QtWidgets/QWidget>

namespace Ui {
class HStyleWidget;
}

HE_CONTROL_BEGIN_NAMESPACE

class HStyleWidgetPrivate;

class HStyleWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HStyleWidget(QWidget *parent = nullptr);
    ~HStyleWidget();

private:
    void init();

private:
    Ui::HStyleWidget *ui;
    QScopedPointer<HStyleWidgetPrivate> d_ptr;
};

HE_CONTROL_END_NAMESPACE

#endif // HSTYLEWIDGET_H
