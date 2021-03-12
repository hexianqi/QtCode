/***************************************************************************************************
**      2019-09-09  HBearingCircular 轴承状
***************************************************************************************************/

#pragma once

#include "HAbstractCircular.h"
#include <QtGui/QColor>

HE_CONTROL_BEGIN_NAMESPACE

class HBearingCircularPrivate;

class HBearingCircular : public HAbstractCircular
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HBearingCircular)
    Q_PROPERTY(QColor background READ background WRITE setBackground)
    Q_PROPERTY(QColor foreground READ foreground WRITE setForeground)

public:
    explicit HBearingCircular(QObject *parent = nullptr);

public:
    void initialize(QVariantMap param) override;
    QString typeName() override;

public:
    void draw(QPainter *, double factor, QVariantMap param = QVariantMap()) override;

public:
    QColor background() const;
    QColor foreground() const;

public slots:
    void setBackground(const QColor &value);
    void setForeground(const QColor &value);

protected:
    HBearingCircular(HBearingCircularPrivate &p, QObject *parent = nullptr);
};

HE_CONTROL_END_NAMESPACE
