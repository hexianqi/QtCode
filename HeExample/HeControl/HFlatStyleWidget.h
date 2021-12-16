/***************************************************************************************************
**      2019-06-14  HFlatStyleWidget
***************************************************************************************************/

#pragma once

#include "HNamespace.h"
#include <QtWidgets/QWidget>

namespace Ui {
class HFlatStyleWidget;
}

HE_BEGIN_NAMESPACE

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

HE_END_NAMESPACE
