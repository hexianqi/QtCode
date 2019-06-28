/***************************************************************************************************
**      2019-06-17  HLightButton 高亮发光按钮控件。
**                  http://www.qtcn.org/bbs/read-htm-tid-63464.html
**                  1：可设置文本,居中显示
**                  2：可设置文本颜色
**                  3：可设置外边框渐变颜色
**                  4：可设置里边框渐变颜色
**                  5：可设置背景色
**                  6：可设置是否在容器中可移动,当成一个对象使用
***************************************************************************************************/

#ifndef HLIGHTBUTTON_H
#define HLIGHTBUTTON_H

#include "HControlGlobal.h"
#include <QtWidgets/QWidget>

HE_CONTROL_BEGIN_NAMESPACE

class HLightButtonPrivate;

class HLightButton : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QString text READ text WRITE setText)
    Q_PROPERTY(QColor textColor READ textColor WRITE setTextColor)
    Q_PROPERTY(QColor borderOutColorStart READ borderOutColorStart WRITE setBorderOutColorStart)
    Q_PROPERTY(QColor borderOutColorEnd READ borderOutColorEnd WRITE setBorderOutColorEnd)
    Q_PROPERTY(QColor borderInColorStart READ borderInColorStart WRITE setBorderInColorStart)
    Q_PROPERTY(QColor borderInColorEnd READ borderInColorEnd WRITE setBorderInColorEnd)
    Q_PROPERTY(QColor background READ background WRITE setBackground)
    Q_PROPERTY(QColor overlayColor READ overlayColor WRITE setOverlayColor)
    Q_PROPERTY(bool moveEnable READ isMoveEnable WRITE setMoveEnable)
    Q_PROPERTY(bool showOverlay READ isShowOverlay WRITE setShowOverlay)


public:
    explicit HLightButton(QWidget *parent = nullptr);
    ~HLightButton() override;

public:
    void setText(const QString &value);
    void setTextColor(const QColor &value);
    void setBorderOutColorStart(const QColor &value);
    void setBorderOutColorEnd(const QColor &value);
    void setBorderInColorStart(const QColor &value);
    void setBorderInColorEnd(const QColor &value);
    void setBackground(const QColor &value);
    void setOverlayColor(const QColor &value);
    void setMoveEnable(bool b);
    void setShowOverlay(bool b);

public:
    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;
    QString text() const;
    QColor textColor() const;
    QColor borderOutColorStart() const;
    QColor borderOutColorEnd() const;
    QColor borderInColorStart() const;
    QColor borderInColorEnd() const;
    QColor background() const;
    QColor overlayColor() const;
    bool isMoveEnable() const;
    bool isShowOverlay() const;


protected:
    HLightButton(HLightButtonPrivate &p, QWidget *parent = nullptr);

protected:
    bool eventFilter(QObject *, QEvent *) override;
    void paintEvent(QPaintEvent *) override;
    void drawBorderOut(QPainter *);
    void drawBorderIn(QPainter *);
    void drawBackground(QPainter *);
    void drawText(QPainter *);
    void drawOverlay(QPainter *);

protected:
    QScopedPointer<HLightButtonPrivate> d_ptr;

private:
    void init();
};

HE_CONTROL_END_NAMESPACE

#endif // HLIGHTBUTTON_H
