/***************************************************************************************************
**      2019-06-14  HFlatStyleWidget
***************************************************************************************************/

#ifndef HFLATSTYLEWIDGET_H
#define HFLATSTYLEWIDGET_H

#include "HControlGlobal.h"
#include <QtWidgets/QWidget>

namespace Ui {
class HFlatStyleWidget;
}

HE_CONTROL_BEGIN_NAMESPACE

class HFlatStyleWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HFlatStyleWidget(QWidget *parent = nullptr);
    ~HFlatStyleWidget();

private:
    void init();

private:
    Ui::HFlatStyleWidget *ui;
};

HE_CONTROL_END_NAMESPACE

#endif // HFLATSTYLEWIDGET_H
