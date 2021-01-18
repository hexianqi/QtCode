#ifndef HTESTWIDGET2000_H
#define HTESTWIDGET2000_H

#include "HeGui/HTestWidget2.h"

HE_GUI_USE_NAMESPACE

class HTestWidget2000Private;

class HTestWidget2000 : public HTestWidget2
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
    void handleAction(HActionType action) override;
    void clearResult() override;

protected:
    void init() override;
    void closeEvent(QCloseEvent *) override;
    void createAction() override;
    void createWidget() override;
    void createMenu() override;
    void createToolBar() override;

protected:
    virtual void readSettings();
    virtual void writeSettings();
    virtual void postProcess();
    virtual void refreshWidget(bool append);
    void handleStateChanged(bool b);
    void handleResultChanged(HActionType, bool);
    void openCieWidget();
    void resetGrade();
    void removeResult2();
    void exportDatabase2();
    void importCurve();
    void exportCurve();
};

#endif // HTESTWIDGET2000_H
