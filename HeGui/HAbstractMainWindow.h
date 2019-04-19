/***************************************************************************************************
**      2019-03-01  HAbstractMainWindow 主窗口。
***************************************************************************************************/

#ifndef HMAINWINDOW_H
#define HMAINWINDOW_H

#include "IMainWindow.h"
#include "HeCore/HActionType.h"
#include "HeCore/HCallorHelper.h"

HE_CORE_USE_NAMESPACE

HE_GUI_BEGIN_NAMESPACE

class HMainWindowPrivate;

class HE_GUI_EXPORT HAbstractMainWindow : public IMainWindow, public IConstructorCall
{
    Q_OBJECT

public:
    explicit HAbstractMainWindow(QWidget *parent = nullptr);
    ~HAbstractMainWindow() override;

protected:
    HAbstractMainWindow(HMainWindowPrivate &p, const HCallorHelper &helper, QWidget *parent = nullptr);

protected slots:
    void showDeviceFailed(QString text);
    void showActionFailed(HActionType action, QString text);
    void updateStatusBar(QStringList list);
    void updateLabel(QString name, int state);
    void updatetWindowTitle();

protected slots:
    void open();
    void save(bool b = true);
    void saveAs();
    void importFile(QAction *);
    void exportFile(QAction *);
    void about();

protected:
    virtual void initialize() override;
    virtual void initImportExport();
    virtual void createAction();
    virtual void createActionGroup();
    virtual void createMenu();
    virtual void createToolBar();
    virtual void createToolBarLogo();
    virtual void initMenu();
    virtual void initToolBar();
    virtual void initStatusBar();
    virtual void initBuilder() = 0;
    virtual void initModel();
    virtual void initCentralWidget();

protected:
    virtual QString summary();

protected:
    QScopedPointer<HMainWindowPrivate> d_ptr;
};

HE_GUI_END_NAMESPACE

#endif // HMAINWINDOW_H
