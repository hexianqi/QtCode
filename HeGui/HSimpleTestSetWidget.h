#ifndef HSIMPLETESTSETWIDGET_H
#define HSIMPLETESTSETWIDGET_H

#include "HAbstractTestSetWidget.h"

namespace Ui {
class HSimpleTestSetWidget;
}

HE_GUI_BEGIN_NAMESPACE

class HSimpleTestSetWidgetPrivate;

class HSimpleTestSetWidget : public HAbstractTestSetWidget
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HSimpleTestSetWidget)

public:
    explicit HSimpleTestSetWidget(QWidget *parent = nullptr);
    ~HSimpleTestSetWidget();

public:
    void initialize(QVariantMap param) override;
    QString typeName() override;

public:
    void handleAction(HActionType action) override;
    bool setTestState(bool b) override;

protected slots:
    void on_doubleSpinBox_01_editingFinished();
    void on_checkBox_01_clicked(bool b);
    void on_checkBox_02_clicked(bool b);

private:
    void init();

private:
    Ui::HSimpleTestSetWidget *ui;
};

HE_GUI_END_NAMESPACE

#endif // HSIMPLETESTSETWIDGET_H
