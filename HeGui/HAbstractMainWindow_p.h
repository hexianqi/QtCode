#pragma once

#include "HAbstractMainWindow.h"
#include <QtCore/QMap>

class QLabel;
class QActionGroup;

HE_BEGIN_NAMESPACE

class IModel;
class IBuilder;
class ITestWidget;
class IMementoCollection;

class HAbstractMainWindowPrivate
{
public:
    HAbstractMainWindowPrivate();

public:
    bool showLogo = false;

public:
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
    QMenu *menuHelp = nullptr;

public:
    QToolBar *toolBarLogo = nullptr;
};

HE_END_NAMESPACE
