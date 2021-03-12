/***************************************************************************************************
**      2019-03-01  HAbstractMainWindow 主窗口。
***************************************************************************************************/

#pragma once

#include "IMainWindow.h"
#include "HeCore/HActionType.h"
#include "HeCore/HCallorHelper.h"

HE_CORE_USE_NAMESPACE

HE_GUI_BEGIN_NAMESPACE

class HAbstractMainWindowPrivate;

class HE_GUI_EXPORT HAbstractMainWindow : public IMainWindow, public IConstructorCall
{
    Q_OBJECT

public:
    explicit HAbstractMainWindow(QWidget *parent = nullptr);
    ~HAbstractMainWindow() override;

public:
    QAction *insertMenu(QMenu *) override;
    bool openDialog(QDialog *) override;
    void openWidget(QWidget *) override;

protected:
    HAbstractMainWindow(HAbstractMainWindowPrivate &p, const HCallorHelper &helper, QWidget *parent = nullptr);

protected slots:
    void showDeviceFailed(const QString &port, const QString &text);
    void showActionFailed(HActionType action, const QString &text);
    void updateStatusBar(QStringList list);
    void updateLabel(const QString &name, int state);
    void updatetWindowTitle();

protected slots:
    virtual void open();
    virtual void save(bool b = true);
    virtual void saveAs();
    virtual void importFile(QAction *);
    virtual void exportFile(QAction *);
    virtual void about();

protected:
    virtual QString summary();

protected:
    virtual void initialize() override;
    virtual void initImportExport();
    virtual void createAction();
    virtual void createMenu();
    virtual void createToolBar();
    virtual void createToolBarLogo();
    virtual void initMenu();
    virtual void initToolBar();
    virtual void initStatusBar();
    virtual void initBuilder() = 0;
    virtual void initModel();
    virtual void initCentralWidget();
    virtual void initWindow();

    void readSettings();
    void writeSettings();

protected:
    QScopedPointer<HAbstractMainWindowPrivate> d_ptr;
};

HE_GUI_END_NAMESPACE
