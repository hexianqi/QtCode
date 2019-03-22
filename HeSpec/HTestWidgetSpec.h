#ifndef HTESTWIDGETSPEC_H
#define HTESTWIDGETSPEC_H

#include "HeGui/HAbstractTestWidget.h"

namespace Ui {
class HTestWidgetSpec;
}

HE_GUI_USE_NAMESPACE

class HTestWidgetSpecPrivate;

class HTestWidgetSpec : public HAbstractTestWidget
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HTestWidgetSpec)

public:
    explicit HTestWidgetSpec(QWidget *parent = nullptr);
    ~HTestWidgetSpec();

public:
    QString typeName() override;

protected slots:
    void actionDone(HActionType action) override;

private:
    Ui::HTestWidgetSpec *ui;
};

#endif // HTESTWIDGETSPEC_H
