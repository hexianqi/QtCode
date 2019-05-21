/***************************************************************************************************
**      2018-06-19  HPluginHelper 插件帮助类。
***************************************************************************************************/

#ifndef HPLUGINHELPER_H
#define HPLUGINHELPER_H

#include <QtUiPlugin/QDesignerExportWidget>

class QString;
class QStringList;
class QAction;
class QWidget;
class QTableView;
class QTableWidget;
class QSpinBox;
class QDoubleSpinBox;
class QInputDialog;
class QImage;
class QSize;
class QPen;
class QPolygonF;
class QPointF;

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

public:
    static bool selectedParameter(QWidget *parent, QStringList optional, QString &selected);                     //选择参数
    static bool getInputText(QWidget *parent, QString label, QString &text);

public:
    static QImage createCrossImage(QSize size, QPen pen);
    static QPolygonF calcEllipse(QPointF center, double r, double theta, double a, double b);

};

#endif // HPLUGINHELPER_H
