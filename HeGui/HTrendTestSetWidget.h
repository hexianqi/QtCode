#pragma once

#include "HAbstractTestSetWidget.h"

namespace Ui {
class HTrendTestSetWidget;
}

HE_BEGIN_NAMESPACE

class HTrendTestSetWidgetPrivate;

class HTrendTestSetWidget : public HAbstractTestSetWidget
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HTrendTestSetWidget)

public:
    explicit HTrendTestSetWidget(QWidget *parent = nullptr);
    ~HTrendTestSetWidget() override;

public:
    QString typeName() override;

public:
    void handleAction(HActionType action) override;
    bool setTestState(bool b) override;

protected slots:
    void setCurrentGears(int value);

private:
    void init();

private:
    Ui::HTrendTestSetWidget *ui;
};

HE_END_NAMESPACE

