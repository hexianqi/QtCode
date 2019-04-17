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

class HE_GUI_EXPORT HMainWindowPrivate
{
public:
    HMainWindowPrivate(HAbstractMainWindow *);

public:
    HAbstractMainWindow *q_ptr;
    IBuilder *builder;
    IModel *model;
    ITestWidget *testWidget;

public:
    QMap<QString, quint32> importExport;
    QMap<QString, QLabel *> labels;

public:
    QPixmap logo;

public:
    QAction *actionOpen;
    QAction *actionSave;
    QAction *actionSaveAs;
    QAction *actionExit;
//    QAction *actionStartThread;
//    QAction *actionStopThread;
//    QAction *actionProductInfoEdit;
//    QAction *actionDatabaseDWidget;
//    QAction *actionDatabaseTWidget;
    QAction *actionAbout;
    QAction *actionSeparator;
    QActionGroup *actionGroupImport;
    QActionGroup *actionGroupExport;

public:
    QMenu *menuFile;
    QMenu *menuImport;
    QMenu *menuExport;
    QMenu *menuDatabase;
    QMenu *menuHelp;

public:
    QToolBar *toolBarLogo;
};

HE_GUI_END_NAMESPACE

#endif // HMAINWINDOW_P_H
