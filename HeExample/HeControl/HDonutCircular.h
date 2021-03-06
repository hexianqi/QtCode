/***************************************************************************************************
**      2019-06-20  HDonutCircular 环状
***************************************************************************************************/

#ifndef HDONUTCIRCULAR_H
#define HDONUTCIRCULAR_H

#include "HAbstractCircular.h"
#include <QtGui/QColor>

HE_CONTROL_BEGIN_NAMESPACE

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
    ~HDonutCircular() override;

public:
    void initialize(QVariantMap param) override;
    QString typeName() override;

public:
    void draw(QPainter *, QVariantMap param = QVariantMap()) override;

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

HE_CONTROL_END_NAMESPACE

#endif // HDONUTCIRCULAR_H
