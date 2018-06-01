#ifndef HMAINWINDOW_P_H
#define HMAINWINDOW_P_H

#include "HMainWindow.h"
#include <QMap>

class QLabel;
class QActionGroup;

HE_GUI_BEGIN_NAMESPACE

class HE_GUI_EXPORT HMainWindowPrivate
{
public:
    HMainWindowPrivate(HMainWindow *p);

public:
    HMainWindow *q_ptr;
    QString summary;
    QString cfgFileName;
    IConfigManage *configManage;
    IModel *model;

public:
    QMap<QString, quint32> importExport;
    QMap<QString, QLabel *> labels;

public:
    QAction *actionOpen;
    QAction *actionSave;
    QAction *actionSaveAs;
    QAction *actionExit;
    QAction *actionStartThread;
    QAction *actionStopThread;
    QAction *actionProductInfoEdit;
    QAction *actionDatabaseDWidget;
    QAction *actionDatabaseTWidget;
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
};

HE_GUI_END_NAMESPACE

#endif // HMAINWINDOW_P_H
