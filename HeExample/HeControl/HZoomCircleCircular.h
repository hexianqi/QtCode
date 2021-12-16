/***************************************************************************************************
**      2019-06-20  HCircleZoomCircular 圆缩放
***************************************************************************************************/

#pragma once

#include "HAbstractCircular.h"
#include <QtGui/QColor>

HE_BEGIN_NAMESPACE

class HZoomCircleCircularPrivate;

class HZoomCircleCircular : public HAbstractCircular
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HZoomCircleCircular)
    Q_PROPERTY(QColor foreground READ foreground WRITE setForeground)
    Q_PROPERTY(int minimum READ minimum WRITE setMinimum)
    Q_PROPERTY(bool bounce READ bounce WRITE setBounce)

public:
    explicit HZoomCircleCircular(QObject *parent = nullptr);

public:
    void initialize(QVariantMap param = QVariantMap()) override;
    QString typeName() override;

public:
    void draw(QPainter *, double factor, QVariantMap param = QVariantMap()) override;

public:
    QColor foreground() const;
    double minimum() const;
    bool bounce() const;

public slots:
    void setForeground(const QColor &value);
    void setMinimum(int value);
    void setBounce(bool b);

protected:
    HZoomCircleCircular(HZoomCircleCircularPrivate &p, QObject *parent = nullptr);

protected:
    double calcRaidous(double value);
};

HE_END_NAMESPACE
