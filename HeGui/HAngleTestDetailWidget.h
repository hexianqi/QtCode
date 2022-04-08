#pragma once

#include "HAbstractTestDetailWidget.h"

namespace Ui {
class HAngleTestDetailWidget;
}

HE_BEGIN_NAMESPACE

class HAngleTestDetailWidgetPrivate;

class HAngleTestDetailWidget : public HAbstractTestDetailWidget
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HAngleTestDetailWidget)

public:
    explicit HAngleTestDetailWidget(QWidget *parent = nullptr);
    ~HAngleTestDetailWidget();

public:
    QString typeName() override;

public:
    void refreshWidget() override;
    void refreshData(QString) override;

private:
    Ui::HAngleTestDetailWidget *ui;
};

HE_END_NAMESPACE
