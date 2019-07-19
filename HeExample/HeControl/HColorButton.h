/***************************************************************************************************
**      2019-07-16  HColorButton 多样式超级按钮控件
**                  http://www.qtcn.org/bbs/read-htm-tid-85978-ds-1.html#tpc
**                  1:可设置圆角角度,边框宽度
**                  2:可设置角标和正文文字内容/字体/对齐方式/颜色
**                  3:可设置边框颜色,正常颜色,按下颜色
**                  4:可设置背景图片
**                  5:可设置按钮颜色模式
***************************************************************************************************/

#ifndef HCOLORBUTTON_H
#define HCOLORBUTTON_H

#include "HControlGlobal.h"
#include <QtWidgets/QWidget>

HE_CONTROL_BEGIN_NAMESPACE

class HColorButtonPrivate;

class HColorButton : public QWidget
{
    Q_OBJECT
    Q_ENUMS(ColorMode)
    Q_PROPERTY(QPixmap background READ background WRITE setBackground)
    Q_PROPERTY(int borderRadius READ borderRadius WRITE setBorderRadius)
    Q_PROPERTY(int borderWidth READ borderWidth WRITE setBorderWidth)
    Q_PROPERTY(QColor borderColor READ borderColor WRITE setBorderColor)

    Q_PROPERTY(QString text READ text WRITE setText)
    Q_PROPERTY(QFont textFont READ textFont WRITE setTextFont)
    Q_PROPERTY(Qt::Alignment textAlign READ textAlign WRITE setTextAlign)
    Q_PROPERTY(QColor textColor READ textColor WRITE setTextColor)

    Q_PROPERTY(bool showSuperText READ isShowSuperText WRITE setShowSuperText)
    Q_PROPERTY(QString superText READ superText WRITE setSuperText)
    Q_PROPERTY(QFont superTextFont READ superTextFont WRITE setSuperTextFont)
    Q_PROPERTY(Qt::Alignment superTextAlign READ superTextAlign WRITE setSuperTextAlign)
    Q_PROPERTY(QColor superTextColor READ superTextColor WRITE setSuperTextColor)

    Q_PROPERTY(QColor normalColor READ normalColor WRITE setNormalColor)
    Q_PROPERTY(QColor pressedColor READ pressedColor WRITE setPressedColor)
    Q_PROPERTY(ColorMode colorMode READ colorMode WRITE setColorMode)

    Q_PROPERTY(bool moveEnable READ isMoveEnable WRITE setMoveEnable)

public:
    enum ColorMode
    {
        ColorMode_Normal = 0,       // 松开按下两种颜色
        ColorMode_Replace = 1,      // 按下松开颜色上下交替
        ColorMode_Shade = 2         // 按下松开颜色渐变交替
    };

public:
    explicit HColorButton(QWidget *parent = nullptr);
    ~HColorButton() override;

signals:
    void clicked();
    void pressed();
    void released();

public:
    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;
    QPixmap background() const;
    int borderRadius() const;
    int borderWidth() const;
    QColor borderColor() const;
    QString text() const;
    QFont textFont() const;
    Qt::Alignment textAlign() const;
    QColor textColor() const;
    bool isShowSuperText() const;
    QString superText() const;
    QFont superTextFont() const;
    Qt::Alignment superTextAlign() const;
    QColor superTextColor() const;
    QColor normalColor() const;
    QColor pressedColor() const;
    ColorMode colorMode() const;
    bool isMoveEnable() const;

public slots:
    void setBackground(const QPixmap &value);
    void setBorderRadius(int value);
    void setBorderWidth(int value);
    void setBorderColor(const QColor &value);
    void setText(const QString &value);
    void setTextFont(const QFont &value);
    void setTextAlign(Qt::Alignment value);
    void setTextColor(const QColor &value);
    void setShowSuperText(bool b);
    void setSuperText(const QString &value);
    void setSuperTextFont(const QFont &value);
    void setSuperTextAlign(Qt::Alignment value);
    void setSuperTextColor(const QColor &value);
    void setNormalColor(const QColor &value);
    void setPressedColor(const QColor &value);
    void setColorMode(ColorMode value);
    void setMoveEnable(bool b);

protected:
    HColorButton(HColorButtonPrivate &p, QWidget *parent = nullptr);

protected:
    bool eventFilter(QObject *, QEvent *) override;
    void mousePressEvent(QMouseEvent *) override;
    void mouseReleaseEvent(QMouseEvent *) override;
    void paintEvent(QPaintEvent *) override;
    void drawBackground(QPainter *);
    void drawText(QPainter *);

protected:
    QScopedPointer<HColorButtonPrivate> d_ptr;

private:
    void init();

};

HE_CONTROL_END_NAMESPACE

#endif // HCOLORBUTTON_H
