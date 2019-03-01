/***************************************************************************************************
**      2019-03-01  HMainWindow 主窗口。
***************************************************************************************************/

#ifndef HMAINWINDOW_H
#define HMAINWINDOW_H

#include "HGuiGlobal.h"
#include "HeCore/HActionType.h"
#include "HeController/HControllerGlobal.h"
#include "HeData/HDataGlobal.h"
#include <QMainWindow>

HE_CORE_USE_NAMESPACE

HE_CONTROLLER_BEGIN_NAMESPACE
class IModel;
HE_CONTROLLER_END_NAMESPACE
HE_CONTROLLER_USE_NAMESPACE

HE_DATA_BEGIN_NAMESPACE
class IConfigManage;
HE_DATA_END_NAMESPACE
HE_DATA_USE_NAMESPACE

HE_GUI_BEGIN_NAMESPACE

class HMainWindowPrivate;

class HE_GUI_EXPORT HMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit HMainWindow(QWidget *parent = nullptr);
    ~HMainWindow();

signals:
    void configManageChanged(quint32 type);

public:
    virtual void setConfigFile(QString fileName);
    virtual void setConfigManage(IConfigManage *);
    virtual void setModel(IModel *);

protected:
    HMainWindow(HMainWindowPrivate &p, QWidget *parent = nullptr);

protected slots:
    void showDeviceFailed(QString text);
    void showActionFailed(HActionType action, QString text);
    void updateStatusBar(QStringList list);
    void updateLabel(QString name, int state);

protected slots:
    void open();
    void save();
    void saveAs();
    void about();
    void importFile(QAction *);
    void exportFile(QAction *);

protected:
    virtual void init();
    virtual void initImportExport();
    virtual void createAction();
    virtual void createActionGroup();
    virtual void createMenu();
    virtual void createToolBar();
    virtual void createToolBarLogo();
    virtual void createConnect();
    virtual void initMenu();
    virtual void initToolBar();
    virtual void initStatusBar();

protected:
    virtual QString summary();

protected:
    QScopedPointer<HMainWindowPrivate> d_ptr;
};

HE_GUI_END_NAMESPACE

#endif // HMAINWINDOW_H
