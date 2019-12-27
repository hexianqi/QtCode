/***************************************************************************************************
**      2017-12-19  HNavButton 导航按钮控件
**                  http://www.qtcn.org/bbs/read-htm-tid-85593-ds-1.html#tpc
**                  1:可设置文字的左侧+右侧+顶部+底部间隔
**                  2:可设置文字对齐方式
**                  3:可设置显示倒三角/倒三角边长/倒三角位置/倒三角颜色
**                  4:可设置显示图标/图标间隔/图标尺寸/正常状态图标/悬停状态图标/选中状态图标
**                  5:可设置显示边框线条/线条宽度/线条间隔/线条位置/线条颜色
**                  6:可设置正常背景颜色/悬停背景颜色/选中背景颜色
**                  7:可设置正常文字颜色/悬停文字颜色/选中文字颜色
**                  8:可设置背景颜色为画刷颜色
***************************************************************************************************/

#ifndef HNAVBUTTON_H
#define HNAVBUTTON_H

#include "HControlType.h"
#include <QtWidgets/QPushButton>

HE_CONTROL_BEGIN_NAMESPACE

class HNavButtonPrivate;

class HNavButton : public QPushButton
{
    Q_OBJECT
    Q_PROPERTY(int paddingLeft READ paddingLeft WRITE setPaddingLeft)
    Q_PROPERTY(int paddingRight READ paddingRight WRITE setPaddingRight)
    Q_PROPERTY(int paddingTop READ paddingTop WRITE setPaddingTop)
    Q_PROPERTY(int paddingBottom READ paddingBottom WRITE setPaddingBottom)
    Q_PROPERTY(Qt::Alignment textAlign READ textAlign WRITE setTextAlign)

    Q_PROPERTY(bool showTriangle READ isShowTriangle WRITE setShowTriangle)
    Q_PROPERTY(int triangleLen READ triangleLen WRITE setTriangleLen)
    Q_PROPERTY(HControlType::Position trianglePosition READ trianglePosition WRITE setTrianglePosition)
    Q_PROPERTY(QColor triangleColor READ triangleColor WRITE setTriangleColor)

    Q_PROPERTY(bool showIcon READ isShowIcon WRITE setShowIcon)
    Q_PROPERTY(int iconSpace READ iconSpace WRITE setIconSpace)
    Q_PROPERTY(QSize iconSize READ iconSize WRITE setIconSize)
    Q_PROPERTY(QPixmap iconNormal READ iconNormal WRITE setIconNormal)
    Q_PROPERTY(QPixmap iconHover READ iconHover WRITE setIconHover)
    Q_PROPERTY(QPixmap iconCheck READ iconCheck WRITE setIconCheck)

    Q_PROPERTY(bool showLine READ isShowLine WRITE setShowLine)
    Q_PROPERTY(int lineSpace READ lineSpace WRITE setLineSpace)
    Q_PROPERTY(int lineWidth READ lineWidth WRITE setLineWidth)
    Q_PROPERTY(HControlType::Position linePosition READ linePosition WRITE setLinePosition)
    Q_PROPERTY(QColor lineColor READ lineColor WRITE setLineColor)

    Q_PROPERTY(QColor normalBackground READ bormalBackground WRITE setNormalBackground)
    Q_PROPERTY(QColor hoverBackground READ hoverBackground WRITE setHoverBackground)
    Q_PROPERTY(QColor checkBackground READ checkBackground WRITE setCheckBackground)
    Q_PROPERTY(QColor normalTextColor READ normalTextColor WRITE setNormalTextColor)
    Q_PROPERTY(QColor hoverTextColor READ hoverTextColor WRITE setHoverTextColor)
    Q_PROPERTY(QColor checkTextColor READ checkTextColor WRITE setCheckTextColor)

public:
    explicit HNavButton(QWidget *parent = nullptr);
    ~HNavButton() override;

public:
    int paddingLeft() const;
    int paddingRight() const;
    int paddingTop() const;
    int paddingBottom() const;
    Qt::Alignment textAlign() const;
    bool isShowTriangle() const;
    int triangleLen() const;
    HControlType::Position trianglePosition() const;
    QColor triangleColor() const;
    bool isShowIcon() const;
    int iconSpace() const;
    QSize iconSize() const;
    QPixmap iconNormal() const;
    QPixmap iconHover() const;
    QPixmap iconCheck() const;
    bool isShowLine() const;
    int lineSpace() const;
    int lineWidth() const;
    HControlType::Position linePosition() const;
    QColor lineColor() const;
    QColor bormalBackground() const;
    QColor hoverBackground() const;
    QColor checkBackground() const;
    QColor normalTextColor() const;
    QColor hoverTextColor() const;
    QColor checkTextColor() const;

public slots:
    void setPadding(int value);
    void setPadding(int left, int right, int top, int bottom);
    void setPaddingLeft(int value);
    void setPaddingRight(int value);
    void setPaddingTop(int value);
    void setPaddingBottom(int value);
    void setTextAlign(Qt::Alignment value);
    void setShowTriangle(bool b);
    void setTriangleLen(int value);
    void setTrianglePosition(HControlType::Position value);
    void setTriangleColor(const QColor &value);
    void setShowIcon(bool b);
    void setIconSpace(int value);
    void setIconSize(QSize value);
    void setIconNormal(const QPixmap &value);
    void setIconHover(const QPixmap &value);
    void setIconCheck(const QPixmap &value);
    void setShowLine(bool b);
    void setLineSpace(int value);
    void setLineWidth(int value);
    void setLinePosition(HControlType::Position value);
    void setLineColor(const QColor &value);
    void setNormalBackground(const QColor &value);
    void setHoverBackground(const QColor &value);
    void setCheckBackground(const QColor &value);
    void setNormalTextColor(const QColor &value);
    void setHoverTextColor(const QColor &value);
    void setCheckTextColor(const QColor &value);
    void setNormalBackgroundBrush(const QBrush &value);
    void setHoverBackgroundBrush(const QBrush &value);
    void setCheckBackgroundBrush(const QBrush &value);

protected:
    HNavButton(HNavButtonPrivate &p, QWidget *parent = nullptr);

protected:
    void enterEvent(QEvent *) override;
    void leaveEvent(QEvent *) override;
    void paintEvent(QPaintEvent *) override;
    void drawBackground(QPainter *);
    void drawText(QPainter *);
    void drawIcon(QPainter *);
    void drawLine(QPainter *);
    void drawTriangle(QPainter *);

protected:
    QScopedPointer<HNavButtonPrivate> d_ptr;
};

HE_CONTROL_END_NAMESPACE

#endif // HNAVBUTTON_H
