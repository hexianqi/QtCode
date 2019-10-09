/***************************************************************************************************
**      2019-09-05  HPetalCircular 花瓣状
***************************************************************************************************/

#ifndef HPETALCIRCULAR_H
#define HPETALCIRCULAR_H

#include "HAbstractCircular.h"
#include <QtGui/QColor>

HE_CONTROL_BEGIN_NAMESPACE

class HPetalCircularPrivate;

class HPetalCircular : public HAbstractCircular
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HPetalCircular)
    Q_PROPERTY(QColor foreground READ foreground WRITE setForeground)

public:
    explicit HPetalCircular(QObject *parent = nullptr);
    ~HPetalCircular() override;

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
    HPetalCircular(HPetalCircularPrivate &p, QObject *parent = nullptr);
};

HE_CONTROL_END_NAMESPACE

#endif // HPETALCIRCULAR_H
