/***************************************************************************************************
**      2019-09-09  HBubbleCircular 气泡状
***************************************************************************************************/

#ifndef HBUBBLECIRCULAR_H
#define HBUBBLECIRCULAR_H

#include "HAbstractCircular.h"
#include <QtGui/QColor>

HE_CONTROL_BEGIN_NAMESPACE

class HBubbleCircularPrivate;

class HBubbleCircular : public HAbstractCircular
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HBubbleCircular)
    Q_PROPERTY(QColor foreground READ foreground WRITE setForeground)

public:
    explicit HBubbleCircular(QObject *parent = nullptr);
    ~HBubbleCircular() override;

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
    HBubbleCircular(HBubbleCircularPrivate &p, QObject *parent = nullptr);
};

HE_CONTROL_END_NAMESPACE

#endif // HBUBBLECIRCULAR_H
