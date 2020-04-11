#ifndef HMAINWINDOW_P_H
#define HMAINWINDOW_P_H

#include "HAbstractMainWindow.h"
#include "HeController/HControllerGlobal.h"
#include <QtCore/QMap>

class QLabel;
class QActionGroup;

HE_CONTROLLER_BEGIN_NAMESPACE
class IModel;
HE_CONTROLLER_END_NAMESPACE
HE_CONTROLLER_USE_NAMESPACE

HE_GUI_BEGIN_NAMESPACE

class IBuilder;
class ITestWidget;

class HE_GUI_EXPORT HAbstractMainWindowPrivate
{
public:
    HAbstractMainWindowPrivate(HAbstractMainWindow *);

public:
    bool showLogo = false;

public:
    HAbstractMainWindow *q_ptr = nullptr;
    IBuilder *builder = nullptr;
    IModel *model = nullptr;
    ITestWidget *testWidget = nullptr;

public:
    QMap<QString, quint32> importExport;
    QMap<QString, QLabel *> labels;

public:
    QPixmap logo;

public:
    QAction *actionOpen = nullptr;
    QAction *actionSave = nullptr;
    QAction *actionSaveAs = nullptr;
    QAction *actionExit = nullptr;
    QAction *actionAbout = nullptr;
    QAction *actionSeparator = nullptr;
    QActionGroup *actionGroupImport = nullptr;
    QActionGroup *actionGroupExport = nullptr;

public:
    QMenu *menuFile = nullptr;
    QMenu *menuImport = nullptr;
    QMenu *menuExport = nullptr;
    QMenu *menuDatabase = nullptr;
    QMenu *menuHelp = nullptr;

public:
    QToolBar *toolBarLogo = nullptr;
};

HE_GUI_END_NAMESPACE

#endif // HMAINWINDOW_P_H
