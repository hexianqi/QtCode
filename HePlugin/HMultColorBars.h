/***************************************************************************************************
**      2021-12-02  HMultColorBars
***************************************************************************************************/

#pragma once

#include "third/qcustomplot.h"

class HMultColorBarsPrivate;

class HMultColorBars : public QCPBars
{
    Q_OBJECT

public:
    explicit HMultColorBars(QCPAxis *keyAxis, QCPAxis *valueAxis);
    ~HMultColorBars() override;

public:
    bool labelVisible() const;
    Qt::Alignment labelAligment() const;
    double labelSpace() const;
    QFont labelFont() const;

public:
    void setLabelVisible(bool);
    void setLabelAlignment(Qt::Alignment);
    void setLabelSpace(double);
    void setLabelFont(const QFont &);

protected:
    HMultColorBars(HMultColorBarsPrivate &p, QCPAxis *keyAxis, QCPAxis *valueAxis);

protected:
    void draw(QCPPainter *painter) override;
    void drawLabel(QCPPainter *painter, QString text, QRectF barRect);

protected:
    QScopedPointer<HMultColorBarsPrivate> d_ptr;
};



