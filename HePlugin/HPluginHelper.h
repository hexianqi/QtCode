/***************************************************************************************************
**      2018-06-19  HPluginHelper 插件帮助类。
***************************************************************************************************/

#ifndef HPLUGINHELPER_H
#define HPLUGINHELPER_H

#include <QtUiPlugin/QDesignerExportWidget>

class QString;
class QAction;
class QWidget;
class QTableView;
class QTableWidget;
class QSpinBox;
class QDoubleSpinBox;
class QInputDialog;

class QDESIGNER_WIDGET_EXPORT HPluginHelper
{
public:
    static QAction *addSeparator(QWidget *widget);

public:
    static QString copy(QTableWidget *widget, bool withHeader = false);
    static QString copy(QTableView *widget, bool withHeader = false);
    static QString paste(QTableWidget *widget);
    static QString paste(QTableView *widget);

public:
    static void initWidget(QString type, QSpinBox *widget);
    static void initWidget(QString type, QDoubleSpinBox *widget);
    static void initWidget(QString type, QInputDialog *dlg);
};

#endif // HPLUGINHELPER_H
