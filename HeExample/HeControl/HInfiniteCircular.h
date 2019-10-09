/***************************************************************************************************
**      2019-09-09  HInfiniteCircular 无限状
***************************************************************************************************/

#ifndef HINFINITECIRCULAR_H
#define HINFINITECIRCULAR_H

#include "HAbstractCircular.h"
#include <QtGui/QColor>

HE_CONTROL_BEGIN_NAMESPACE

class HInfiniteCircularPrivate;

class HInfiniteCircular : public HAbstractCircular
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HInfiniteCircular)
    Q_PROPERTY(QColor background READ background WRITE setBackground)
    Q_PROPERTY(QColor foreground READ foreground WRITE setForeground)

public:
    explicit HInfiniteCircular(QObject *parent = nullptr);
    ~HInfiniteCircular() override;

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
    HInfiniteCircular(HInfiniteCircularPrivate &p, QObject *parent = nullptr);
};

HE_CONTROL_END_NAMESPACE

#endif // HINFINITECIRCULAR_H
