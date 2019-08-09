/***************************************************************************************************
**      2019-08-05  HHueSatRadialPicker
***************************************************************************************************/

#ifndef HHUESATRADIALPICKER_H
#define HHUESATRADIALPICKER_H

#include "HControlGlobal.h"
#include <QtWidgets/QWidget>

HE_CONTROL_BEGIN_NAMESPACE

class HHueSatRadialPickerPrivate;

class HHueSatRadialPicker : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(int value READ value WRITE setValue)
    Q_PROPERTY(QColor color READ color WRITE setColor)

public:
    explicit HHueSatRadialPicker(QWidget *parent = nullptr);
    ~HHueSatRadialPicker() override;

signals:
    void valueChanged(int);
    void colorPicked(const QColor &);

public:
    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;
    int heightForWidth(int) const override;
    int value() const;
    QColor color() const;

public slots:
    void setValue(int value);
    void setColor(const QColor &value);

protected:
    HHueSatRadialPicker(HHueSatRadialPickerPrivate &p, QWidget *parent = nullptr);

protected:
    void mousePressEvent(QMouseEvent *) override;
    void mouseMoveEvent(QMouseEvent *) override;
    void resizeEvent(QResizeEvent *) override;
    void paintEvent(QPaintEvent *) override;
    void drawCrosshair(QPainter *, const QPointF &);

protected:
    QScopedPointer<HHueSatRadialPickerPrivate> d_ptr;

private:
    void init();
    void buildGradient(int value);
    void buildPixmap();
    void colorPick(const QPointF &point, double radius);
    double radius(const QPointF &);
    double hue(const QPointF &);
};

HE_CONTROL_END_NAMESPACE

#endif // HHUESATRADIALPICKER_H
