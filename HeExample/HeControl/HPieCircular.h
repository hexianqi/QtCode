/***************************************************************************************************
**      2019-06-20  HPieCircular 饼状
***************************************************************************************************/

#ifndef HPIECIRCULAR_H
#define HPIECIRCULAR_H

#include "HAbstractCircular.h"
#include <QtGui/QColor>

HE_CONTROL_BEGIN_NAMESPACE

class HPieCircularPrivate;

class HPieCircular : public HAbstractCircular
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HPieCircular)
    Q_PROPERTY(QColor background READ background WRITE setBackground)
    Q_PROPERTY(QColor foreground READ foreground WRITE setForeground)
    Q_PROPERTY(int spanAngle READ spanAngle WRITE setSpanAngle)

public:
    explicit HPieCircular(QObject *parent = nullptr);

public:
    void initialize(QVariantMap param) override;
    QString typeName() override;

public:
    void draw(QPainter *, double factor, QVariantMap param = QVariantMap()) override;

public:
    QColor background() const;
    QColor foreground() const;
    int spanAngle() const;

public slots:
    void setBackground(const QColor &);
    void setForeground(const QColor &);
    void setSpanAngle(int value);

protected:
    HPieCircular(HPieCircularPrivate &p, QObject *parent = nullptr);
};

HE_CONTROL_END_NAMESPACE

#endif // HPIECIRCULAR_H
