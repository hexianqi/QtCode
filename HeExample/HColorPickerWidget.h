/***************************************************************************************************
**      2019-05-31  HColorPickerWidget 颜色拾取器。
**                  http://www.qtcn.org/bbs/read-htm-tid-46711.html
***************************************************************************************************/

#ifndef HCOLORPICKERWIDGET_H
#define HCOLORPICKERWIDGET_H

#include "HExampleGlobal.h"
#include <QtWidgets/QWidget>

class QTimer;

namespace Ui {
class HColorPickerWidget;
}

class HE_EXAMPLE_EXPORT HColorPickerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HColorPickerWidget(QWidget *parent = nullptr);
    ~HColorPickerWidget();

public slots:
    void showColorValue();

private:
    void init();

private:
    Ui::HColorPickerWidget *ui;
    QTimer *_timer;
};

#endif // HCOLORPICKERWIDGET_H
