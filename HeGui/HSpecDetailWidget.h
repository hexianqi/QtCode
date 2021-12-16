/***************************************************************************************************
**      2019-04-11  HSpecDetailWidget 光谱详情窗体类。
***************************************************************************************************/

#pragma once

#include "HAbstractTestDetailWidget.h"

namespace Ui {
class HSpecDetailWidget;
}

HE_BEGIN_NAMESPACE

class HSpecDetailWidgetPrivate;

class HSpecDetailWidget : public HAbstractTestDetailWidget
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HSpecDetailWidget)

public:
    explicit HSpecDetailWidget(QWidget *parent = nullptr);
    ~HSpecDetailWidget() override;

public:
    QString typeName() override;

public:
    void refreshWidget() override;

private:
    Ui::HSpecDetailWidget *ui;
};

HE_END_NAMESPACE
