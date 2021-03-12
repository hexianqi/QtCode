/***************************************************************************************************
**      2019-08-05  HHueSatPicker
***************************************************************************************************/

#pragma once

#include "HControlGlobal.h"
#include <QtWidgets/QFrame>

HE_CONTROL_BEGIN_NAMESPACE

class HHueSatPickerPrivate;

class HHueSatPicker : public QFrame
{
    Q_OBJECT
    Q_PROPERTY(int minimumHue READ minimumHue WRITE setMinimumHue)
    Q_PROPERTY(int maximumHue READ maximumHue WRITE setMaximumHue)
    Q_PROPERTY(int minimumSat READ minimumSat WRITE setMinimumSat)
    Q_PROPERTY(int maximumSat READ maximumSat WRITE setMaximumSat)
    Q_PROPERTY(int value READ value WRITE setValue)
    Q_PROPERTY(QColor color READ color WRITE setColor)

public:
    explicit HHueSatPicker(QWidget *parent = nullptr);
    ~HHueSatPicker() override;

signals:
    void colorPicked(const QColor &);
    void satChanged(int, int);
    void hueChanged(int, int);
    void valueChanged(int);


public:
    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;
    int minimumHue() const;
    int maximumHue() const;
    int minimumSat() const;
    int maximumSat() const;
    int value() const;
    QColor color() const;

public slots:
    void setHueRange(int minimum, int maximum);
    void setSatRange(int minimum, int maximum);
    void setMinimumHue(int value);
    void setMaximumHue(int value);
    void setMinimumSat(int value);
    void setMaximumSat(int value);
    void setValue(int value);
    void setColor(const QColor &value);

protected:
    HHueSatPicker(HHueSatPickerPrivate &p, QWidget *parent = nullptr);

protected:
    void mousePressEvent(QMouseEvent *) override;
    void mouseMoveEvent(QMouseEvent *) override;
    void resizeEvent(QResizeEvent *) override;
    void paintEvent(QPaintEvent *) override;

protected:
    QScopedPointer<HHueSatPickerPrivate> d_ptr;

private:
    void init();
    void buildPixmap();
    void colorPick(const QPointF &);
    double hueFromX(double) const;
    double hueToX(double) const;
    double satFromY(double) const;
    double satToY(double) const;

};

HE_CONTROL_END_NAMESPACE
