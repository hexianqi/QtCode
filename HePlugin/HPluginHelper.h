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
    // 添加分隔符
    static QAction *addSeparator(QWidget *);

public:
    // 复制
    static QString copy(QTableWidget *, bool withHeader = false);
    static QString copy(QTableView *, bool withHeader = false);
    // 粘贴
    static QString paste(QTableWidget *);
    static QString paste(QTableView *);

public:
    static void initWidget(QString type, QSpinBox *);
    static void initWidget(QString type, QDoubleSpinBox *);
    static void initWidget(QString type, QInputDialog *);
    // 窗体居中桌面
    static void centerWidget(QWidget *);

public:
    // 选择参数
    static bool selectedParameter(QWidget *parent, QStringList optional, QString &selected);
    // 获取输入文本
    static bool getInputText(QWidget *parent, QString label, QString &text);

public:
    // 创建十字图片
    static QImage createCrossImage(QSize size, QPen pen);
    // 计算椭圆
    static QPolygonF calcEllipse(QPointF center, double r, double theta, double a, double b);

};

#endif // HPLUGINHELPER_H
