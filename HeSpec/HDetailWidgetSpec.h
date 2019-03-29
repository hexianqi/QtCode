#ifndef HDETAILWIDGETSPEC_H
#define HDETAILWIDGETSPEC_H

#include "HeGui/HAbstractDetailWidget.h"

HE_GUI_USE_NAMESPACE

namespace Ui {
class HDetailWidgetSpec;
}

class HDetailWidgetSpecPrivate;

class HDetailWidgetSpec : public HAbstractDetailWidget
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HDetailWidgetSpec)

public:
    explicit HDetailWidgetSpec(QWidget *parent = nullptr);
    ~HDetailWidgetSpec() override;

public:
    QString typeName() override;
    void refreshWidget() override;

private:
    Ui::HDetailWidgetSpec *ui;
};

#endif // HDETAILWIDGETSPEC_H
