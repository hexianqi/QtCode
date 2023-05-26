/***************************************************************************************************
**      2019-03-01  HAbstractMainWindow 主窗口。
***************************************************************************************************/

#pragma once

#include "IMainWindow.h"
#include "HeCore/HActionType.h"

HE_BEGIN_NAMESPACE

class HAbstractMainWindowPrivate;

class HAbstractMainWindow : public IMainWindow
{
    Q_OBJECT

public:
    explicit HAbstractMainWindow(QWidget *parent = nullptr);
    ~HAbstractMainWindow() override;

public:
    void afterConstruction() override;
    void beforeDestruction() override;

public:
    void setAuthority(int) override;
    QAction *insertMenu(QMenu *) override;
    bool blockTestWidget(bool block) override;
    QVariant blockAndRun(std::function<QVariant(QVariantMap)> func, QVariantMap param = QVariantMap()) override;

protected:
    HAbstractMainWindow(HAbstractMainWindowPrivate &p, QWidget *parent = nullptr);

protected slots:
    void showDeviceFailed(const QString &port, const QString &text);
    void showActionFailed(HActionType action, const QString &text);
    void updateStatusBar(QStringList list);
    void updateLabel(const QString &name, int state);
    void updatetWindowTitle();

protected slots:
    virtual void openFile();
    virtual void saveFile();
    virtual void saveAsFile();
    virtual void importFile(QAction *);
    virtual void exportFile(QAction *);
    virtual void about();

protected:
    virtual QString summary();

protected:
    virtual void initialize();
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
    virtual void readSettings();
    virtual void writeSettings();
    void updateAuthority(QList<QAction *> actions, int value);
    void saveMemento();

protected:
    QScopedPointer<HAbstractMainWindowPrivate> d_ptr;
};

HE_END_NAMESPACE
