/***************************************************************************************************
**      2019-04-11  HSpecDetailWidget 光谱详情窗体类。
***************************************************************************************************/

#pragma once

#include "HAbstractTestDetailWidget.h"

namespace Ui {
class HSpecCalibrateDetailWidget;
}

HE_BEGIN_NAMESPACE

class HSpecCalibrateDetailWidgetPrivate;

class HSpecCalibrateDetailWidget : public HAbstractTestDetailWidget
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HSpecCalibrateDetailWidget)

public:
    explicit HSpecCalibrateDetailWidget(QWidget *parent = nullptr);
    ~HSpecCalibrateDetailWidget() override;

public:
    QString typeName() override;

public:
    void refreshWidget() override;

protected:
    void initHash() override;

private:
    Ui::HSpecCalibrateDetailWidget *ui;
};

HE_END_NAMESPACE
