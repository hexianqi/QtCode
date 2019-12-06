/***************************************************************************************************
**      2019-05-31  HColorPickerWidget 颜色拾取器。
**                  http://www.qtcn.org/bbs/read-htm-tid-46711.html
***************************************************************************************************/

#ifndef HCOLORPICKERWIDGET_H
#define HCOLORPICKERWIDGET_H

#include "HControlGlobal.h"
#include <QtWidgets/QWidget>

class QTimer;

namespace Ui {
class HColorPicker;
}

HE_CONTROL_BEGIN_NAMESPACE

class HE_CONTROL_EXPORT HColorPicker : public QWidget
{
    Q_OBJECT

public:
    explicit HColorPicker(QWidget *parent = nullptr);
    ~HColorPicker() override;

public slots:
    void showColorValue();

private:
    void init();

private:
    Ui::HColorPicker *ui;
    QTimer *_timer;
};

HE_CONTROL_END_NAMESPACE

#endif // HCOLORPICKERWIDGET_H
