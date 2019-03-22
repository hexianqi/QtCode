/***************************************************************************************************
**      2019-03-01  HMainWindow 主窗口。
***************************************************************************************************/

#ifndef HMAINWINDOW_H
#define HMAINWINDOW_H

#include "HGuiGlobal.h"
#include "HeCore/HActionType.h"
#include "HeCore/HCallorHelper.h"
#include <QMainWindow>

HE_CORE_USE_NAMESPACE

HE_GUI_BEGIN_NAMESPACE

class HMainWindowPrivate;

class HE_GUI_EXPORT HAbstractMainWindow : public QMainWindow, public IConstructorCall
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
    void save();
    void saveAs();
    void importFile(QAction *);
    void exportFile(QAction *);
    void about();

protected:
    virtual void initialize() override;
    virtual void initImportExport();
    virtual void createBuilder() = 0;
    virtual void createAction();
    virtual void createActionGroup();
    virtual void createMenu();
    virtual void createToolBar();
    virtual void createToolBarLogo();
    virtual void createConnect();
    virtual void initMenu();
    virtual void initToolBar();
    virtual void initStatusBar();
    virtual void initModel();
    virtual void initCentralWidget();

protected:
    virtual QString summary();

protected:
    QScopedPointer<HMainWindowPrivate> d_ptr;
};

HE_GUI_END_NAMESPACE

#endif // HMAINWINDOW_H
