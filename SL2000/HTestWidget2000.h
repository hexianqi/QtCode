#ifndef HTESTWIDGET2000_H
#define HTESTWIDGET2000_H

#include "HeGui/HTestWidget.h"

HE_GUI_USE_NAMESPACE

class HTestWidget2000Private;

class HTestWidget2000 : public HTestWidget
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HTestWidget2000)

public:
    explicit HTestWidget2000(QWidget *parent = nullptr);
    ~HTestWidget2000() override;

protected:
    HTestWidget2000(HTestWidget2000Private &p, QWidget *parent = nullptr);

public:
    void initialize(QVariantMap param) override;
    QString typeName() override;

protected:
    bool setTest(bool b) override;
    void handleAction(HActionType action) override;

protected:
    void createWidget() override;
    void createAction() override;
    void createMenu() override;
    void createToolBar() override;
    void clearResult() override;

protected:
    void handleTestStateChanged(bool b);
    void resetGrade();
    void refreshWidget();    
    void postProcess();
    void importCurve();
    void exportCurve();
    void readSettings();
    void writeSettings();
};

#endif // HTESTWIDGET2000_H
