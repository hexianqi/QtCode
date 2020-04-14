/***************************************************************************************************
**      2019-06-19  HCircleCircular 圈状
***************************************************************************************************/

#ifndef HCIRCLECIRCULAR_H
#define HCIRCLECIRCULAR_H

#include "HAbstractCircular.h"
#include <QtGui/QColor>

HE_CONTROL_BEGIN_NAMESPACE

class HCircleCircularPrivate;

class HCircleCircular : public HAbstractCircular
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HCircleCircular)
    Q_PROPERTY(QColor foreground READ foreground WRITE setForeground)

public:
    explicit HCircleCircular(QObject *parent = nullptr);

public:
    void initialize(QVariantMap param) override;
    QString typeName() override;

public:
    void draw(QPainter *, double factor, QVariantMap param = QVariantMap()) override;

public:
    QColor foreground() const;

public slots:
    void setForeground(const QColor &value);

protected:
    HCircleCircular(HCircleCircularPrivate &p, QObject *parent = nullptr);
};

HE_CONTROL_END_NAMESPACE

#endif // HCIRCLECIRCULAR_H
