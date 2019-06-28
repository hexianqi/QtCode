/***************************************************************************************************
**      2019-06-20  HLineCircular 线状
***************************************************************************************************/

#ifndef HLINECIRCULAR_H
#define HLINECIRCULAR_H

#include "HAbstractCircular.h"
#include <QtGui/QColor>

HE_CONTROL_BEGIN_NAMESPACE

class HLineCircularPrivate;

class HLineCircular : public HAbstractCircular
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HLineCircular)
    Q_PROPERTY(QColor foreground READ foreground WRITE setForeground)

public:
    explicit HLineCircular(QObject *parent = nullptr);
    ~HLineCircular() override;

public:
    void initialize(QVariantMap param) override;
    QString typeName() override;

public:
    void draw(QPainter *, QVariantMap param = QVariantMap()) override;

public:
    QColor foreground() const;

public slots:
    void setForeground(const QColor &value);

protected:
    HLineCircular(HLineCircularPrivate &p, QObject *parent = nullptr);
};

HE_CONTROL_END_NAMESPACE

#endif // HLINECIRCULAR_H
