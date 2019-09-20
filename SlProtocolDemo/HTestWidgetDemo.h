/***************************************************************************************************
**      2019-09-17  HTestWidgetDemo
***************************************************************************************************/

#ifndef HTESTWIDGETDEMO_H
#define HTESTWIDGETDEMO_H

#include "HeData/HDataGlobal.h"
#include "HeGui/HTestWidget.h"

HE_GUI_USE_NAMESPACE

HE_DATA_BEGIN_NAMESPACE
class ISpecCalibrate;
HE_DATA_END_NAMESPACE
HE_DATA_USE_NAMESPACE

class HTestWidgetDemoPrivate;

class HTestWidgetDemo : public HTestWidget
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HTestWidgetDemo)

public:
    explicit HTestWidgetDemo(QWidget *parent = nullptr);
    ~HTestWidgetDemo() override;

public:
    void initialize(QVariantMap param) override;
    QString typeName() override;

public:
    void setSpecCalibrate(ISpecCalibrate *);

protected:
    bool setTest(bool b) override;
    void handleAction(HActionType action) override;

protected:
    void createWidget() override;
    void createMenu() override;
    void createToolBar() override;

protected:
    void handleTestStateChanged(bool b);
    void refreshCcdView();
    void refreshSpecWidget();
};

#endif // HTESTWIDGETDEMO_H
