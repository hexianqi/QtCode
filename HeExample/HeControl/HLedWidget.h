/***************************************************************************************************
**      2019-08-06  HLedWidget
***************************************************************************************************/

#pragma once

#include "HNamespace.h"
#include <QtWidgets/QWidget>

HE_BEGIN_NAMESPACE

class HLedWidgetPrivate;

class HLedWidget : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QColor color READ color WRITE setColor)
    Q_PROPERTY(bool checked READ isChecked WRITE setChecked)
    Q_PROPERTY(ShapeStyle shapeStyle READ shapeStyle WRITE setShapeStyle)
    Q_PROPERTY(int frameWidth READ frameWidth WRITE setFrameWidth)
    Q_PROPERTY(bool animated READ isAnimated WRITE setAnimated)
    Q_PROPERTY(int interval READ interval WRITE setInterval)

public:
    enum ShapeStyle
    {
        ShapeStyle_Circular,
        ShapeStyle_RectangularSunken,
        ShapeStyle_RectangularRaised,
        ShapeStyle_RectangularPlain
    };
    Q_ENUM(ShapeStyle)

public:
    explicit HLedWidget(QWidget *parent = nullptr);
    ~HLedWidget() override;

signals:
    void colorChanged(const QColor &);
    void toggled(bool);
    void clicked();

public:
    QSize sizeHint() const override;
    int heightForWidth(int value) const override;
    QColor color() const;
    bool isChecked() const;
    ShapeStyle shapeStyle() const;
    int frameWidth() const;
    bool isAnimated() const;
    int interval() const;

public slots:
    void setColor(const QColor &value);
    void setChecked(bool b);
    void setShapeStyle(ShapeStyle value);
    void setFrameWidth(int value);
    void setAnimated(bool b);
    void setInterval(int value);
    void toggle();
    void blink();

protected:
    HLedWidget(HLedWidgetPrivate &p, QWidget *parent = nullptr);

protected:
    void mouseReleaseEvent(QMouseEvent *) override;
    void paintEvent(QPaintEvent *) override;

protected:
    QScopedPointer<HLedWidgetPrivate> d_ptr;

private:
    void init();
};

HE_END_NAMESPACE
