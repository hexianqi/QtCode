/***************************************************************************************************
**      2019-06-20  HDonutCircular 环状
***************************************************************************************************/

#pragma once

#include "HAbstractCircular.h"
#include <QtGui/QColor>

HE_BEGIN_NAMESPACE

class HDonutCircularPrivate;

class HDonutCircular : public HAbstractCircular
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HDonutCircular)
    Q_PROPERTY(QColor background READ background WRITE setBackground)
    Q_PROPERTY(QColor foreground READ foreground WRITE setForeground)
    Q_PROPERTY(int spanAngle READ spanAngle WRITE setSpanAngle)

public:
    explicit HDonutCircular(QObject *parent = nullptr);

public:
    void initialize(QVariantMap param = QVariantMap()) override;
    QString typeName() override;

public:
    void draw(QPainter *, double factor, QVariantMap param = QVariantMap()) override;

public:
    QColor background() const;
    QColor foreground() const;
    int spanAngle() const;

public slots:
    void setBackground(const QColor &value);
    void setForeground(const QColor &value);
    void setSpanAngle(int value);

protected:
    HDonutCircular(HDonutCircularPrivate &p, QObject *parent = nullptr);
};

HE_END_NAMESPACE
