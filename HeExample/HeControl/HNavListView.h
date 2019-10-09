/***************************************************************************************************
**      2018-08-15  HNavListView 树状导航栏控件
**                  http://www.qtcn.org/bbs/read-htm-tid-86046-ds-1.html#tpc
**                   1:设置节点数据相当方便,按照对应格式填入即可,分隔符,
**                   2:可设置提示信息 是否显示+宽度
**                   3:可设置行分隔符 是否显示+高度+颜色
**                   4:可设置选中节点线条突出显示+颜色+左侧右侧位置
**                   5:可设置选中节点三角形突出显示+颜色+左侧右侧位置
**                   6:可设置父节点的 选中颜色+悬停颜色+默认颜色
**                   7:可设置子节点的 选中颜色+悬停颜色+默认颜色
**                   8:可设置父节点文字的 图标边距+左侧距离+字体大小+高度
**                   9:可设置子节点文字的 图标边距+左侧距离+字体大小+高度
**                  10:可设置节点展开模式 单击+双击+禁用
***************************************************************************************************/

#ifndef HNAVLISTVIEW_H
#define HNAVLISTVIEW_H

#include "HControlGlobal.h"
#include <QtWidgets/QListView>

HE_CONTROL_BEGIN_NAMESPACE

class HNavListViewPrivate;

class HNavListView : public QListView
{
    Q_OBJECT
    Q_PROPERTY(QString items READ items WRITE setItems)
    Q_PROPERTY(bool rightIconVisible READ isRightIconVisible WRITE setRightIconVisible)
    Q_PROPERTY(bool tipVisible READ isTipVisible WRITE setTipVisible)
    Q_PROPERTY(int tipWidth READ tipWidth WRITE setTipWidth)

    Q_PROPERTY(bool separateVisible READ isSeparateVisible WRITE setSeparateVisible)
    Q_PROPERTY(int separateHeight READ separateHeight WRITE setSeparateHeight)
    Q_PROPERTY(QColor separateColor READ separateColor WRITE setSeparateColor)

    Q_PROPERTY(bool lineVisible READ isLineVisible WRITE setLineVisible)
    Q_PROPERTY(bool lineLeft READ isLineLeft WRITE setLineLeft)
    Q_PROPERTY(int lineWidth READ lineWidth WRITE setLineWidth)
    Q_PROPERTY(QColor lineColor READ lineColor WRITE setLineColor)

    Q_PROPERTY(bool triangleVisible READ isTriangleVisible WRITE setTriangleVisible)
    Q_PROPERTY(bool triangleLeft READ isTriangleLeft WRITE setTriangleLeft)
    Q_PROPERTY(int triangleWidth READ triangleWidth WRITE setTriangleWidth)
    Q_PROPERTY(QColor triangleColor READ triangleColor WRITE setTriangleColor)

    Q_PROPERTY(int parentMargin READ parentMargin WRITE setParentMargin)
    Q_PROPERTY(int parentIconMargin READ parentIconMargin WRITE setParentIconMargin)
    Q_PROPERTY(int parentFontSize READ parentFontSize WRITE setParentFontSize)
    Q_PROPERTY(int parentHeight READ parentHeight WRITE setParentHeight)
    Q_PROPERTY(QColor parentNormalColor READ parentNormalColor WRITE setParentNormalColor)
    Q_PROPERTY(QColor parentSelectedColor READ parentSelectedColor WRITE setParentSelectedColor)
    Q_PROPERTY(QColor parentHoverColor READ parentHoverColor WRITE setParentHoverColor)
    Q_PROPERTY(QColor parentTextNormalColor READ parentTextNormalColor WRITE setParentTextNormalColor)
    Q_PROPERTY(QColor parentTextSelectedColor READ parentTextSelectedColor WRITE setParentTextSelectedColor)
    Q_PROPERTY(QColor parentTextHoverColor READ parentTextHoverColor WRITE setParentTextHoverColor)

    Q_PROPERTY(int childMargin READ childMargin WRITE setChildMargin)
    Q_PROPERTY(int childIconMargin READ childIconMargin WRITE setChildIconMargin)
    Q_PROPERTY(int childFontSize READ childFontSize WRITE setChildFontSize)
    Q_PROPERTY(int childHeight READ childHeight WRITE setChildHeight)
    Q_PROPERTY(QColor childNormalColor READ childNormalColor WRITE setChildNormalColor)
    Q_PROPERTY(QColor childSelectedColor READ childSelectedColor WRITE setChildSelectedColor)
    Q_PROPERTY(QColor childHoverColor READ childHoverColor WRITE setChildHoverColor)
    Q_PROPERTY(QColor childTextNormalColor READ childTextNormalColor WRITE setChildTextNormalColor)
    Q_PROPERTY(QColor childTextSelectedColor READ childTextSelectedColor WRITE setChildTextSelectedColor)
    Q_PROPERTY(QColor childTextHoverColor READ childTextHoverColor WRITE setChildTextHoverColor)

    Q_PROPERTY(ExpendMode expendMode READ expendMode WRITE setExpendMode)

public:
    enum ExpendMode
    {
        ExpendMode_SingleClick = 0, //单击模式
        ExpendMode_DoubleClick = 1, //双击模式
        ExpendMode_NoClick = 2,     //不可单击双击
    };
    Q_ENUM(ExpendMode)


public:
    explicit HNavListView(QWidget *parent = nullptr);
    ~HNavListView() override;

signals:
    void pressed(const QString &text, const QString &parentText);

public:
    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;
    QString items() const;
    bool isRightIconVisible() const;
    bool isTipVisible() const;
    int tipWidth() const;
    bool isSeparateVisible() const;
    int separateHeight() const;
    QColor separateColor() const;
    bool isLineVisible() const;
    bool isLineLeft() const;
    int lineWidth() const;
    QColor lineColor() const;
    bool isTriangleVisible() const;
    bool isTriangleLeft() const;    
    int triangleWidth() const;
    QColor triangleColor() const;
    int parentMargin() const;
    int parentIconMargin() const;
    int parentFontSize() const;
    int parentHeight() const;
    QColor parentNormalColor() const;
    QColor parentSelectedColor() const;
    QColor parentHoverColor() const;
    QColor parentTextNormalColor() const;
    QColor parentTextSelectedColor() const;
    QColor parentTextHoverColor() const;
    int childMargin() const;
    int childIconMargin() const;
    int childFontSize() const;
    int childHeight() const;
    QColor childNormalColor() const;
    QColor childSelectedColor() const;
    QColor childHoverColor() const;
    QColor childTextNormalColor() const;
    QColor childTextSelectedColor() const;
    QColor childTextHoverColor() const;
    ExpendMode expendMode() const;

public slots:
    void readData(const QString &fileName);
    void setCurrentRow(int value);
    void setItems(const QString &value);
    void setRightIconVisible(bool b);
    void setTipVisible(bool b);
    void setTipWidth(int value);
    void setSeparateVisible(bool b);
    void setSeparateHeight(int value);
    void setSeparateColor(const QColor &value);
    void setLineVisible(bool b);
    void setLineLeft(bool b);
    void setLineWidth(int value);
    void setLineColor(const QColor &value);
    void setTriangleVisible(bool b);
    void setTriangleLeft(bool b);   
    void setTriangleWidth(int value);
    void setTriangleColor(const QColor &value);
    void setParentMargin(int value);
    void setParentIconMargin(int value);
    void setParentFontSize(int value);
    void setParentHeight(int value);
    void setParentNormalColor(const QColor &value);
    void setParentSelectedColor(const QColor &value);
    void setParentHoverColor(const QColor &value);
    void setParentTextNormalColor(const QColor &value);
    void setParentTextSelectedColor(const QColor &value);
    void setParentTextHoverColor(const QColor &value);
    void setChildMargin(int value);
    void setChildIconMargin(int value);
    void setChildFontSize(int value);
    void setChildHeight(int value);
    void setChildNormalColor(const QColor &value);
    void setChildSelectedColor(const QColor &value);
    void setChildHoverColor(const QColor &value);
    void setChildTextNormalColor(const QColor &value);
    void setChildTextSelectedColor(const QColor &value);
    void setChildTextHoverColor(const QColor &value);
    void setExpendMode(ExpendMode value);

protected:
    HNavListView(HNavListViewPrivate &p, QWidget *parent = nullptr);

protected:
    QScopedPointer<HNavListViewPrivate> d_ptr;

private:
    void init();
    void handleClicked(const QModelIndex &index);
    void refreshItems();
};

HE_CONTROL_END_NAMESPACE

#endif // HNAVLISTVIEW_H
