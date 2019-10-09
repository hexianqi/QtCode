/***************************************************************************************************
**      2019-08-20  HIconFontWidget 图标字体窗体演示。
***************************************************************************************************/

#ifndef HICONFONTWIDGET_H
#define HICONFONTWIDGET_H

#include "HControlGlobal.h"
#include <QtWidgets/QWidget>

namespace Ui {
class HIconFontWidget;
}

HE_CONTROL_BEGIN_NAMESPACE

class HIconFontWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HIconFontWidget(QWidget *parent = nullptr);
    ~HIconFontWidget();

private:
    void init();

private:
    Ui::HIconFontWidget *ui;
};

HE_CONTROL_END_NAMESPACE

#endif // HICONFONTWIDGET_H
