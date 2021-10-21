#pragma once

#include "HAbstractTestSetWidget.h"

namespace Ui {
class HIVTestSetWidget;
}

HE_GUI_BEGIN_NAMESPACE

class HIVTestSetWidgetPrivate;

class HIVTestSetWidget : public HAbstractTestSetWidget
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HIVTestSetWidget)

public:
    explicit HIVTestSetWidget(QWidget *parent = nullptr);
    ~HIVTestSetWidget() override;

public:
    QString typeName() override;

public:
    void handleAction(HActionType action) override;
    bool setTestState(bool b) override;

protected:
    void initParam();

private:
    void init();

private:
    Ui::HIVTestSetWidget *ui;
};

HE_GUI_END_NAMESPACE
