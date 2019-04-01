#ifndef HTESTWIDGETSPEC_H
#define HTESTWIDGETSPEC_H

#include "HeGui/HAbstractTestWidget.h"

HE_GUI_USE_NAMESPACE

namespace Ui {
class HTestWidgetSpec;
}

class HTestWidgetSpecPrivate;

class HTestWidgetSpec : public HAbstractTestWidget
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HTestWidgetSpec)

public:
    explicit HTestWidgetSpec(QWidget *parent = nullptr);
    ~HTestWidgetSpec() override;

public:
    QString typeName() override;

protected slots:
    void on_pushButton_1_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();
    bool setTest(bool b) override;
    void handleAction(HActionType action) override;
    void handleTestStateChanged(bool b);
    void handleTestModeChanged(int value);
    void handleTestFitStateChanged(bool b);

protected:
    void refreshCcdWidget(int i);
    void refreshSpecWidget();

private:
    void init();

private:
    Ui::HTestWidgetSpec *ui;
};

#endif // HTESTWIDGETSPEC_H
