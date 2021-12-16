/***************************************************************************************************
**      2019-09-09  HBubbleCircular 气泡状
***************************************************************************************************/

#pragma once

#include "HAbstractCircular.h"
#include <QtGui/QColor>

HE_BEGIN_NAMESPACE

class HBubbleCircularPrivate;

class HBubbleCircular : public HAbstractCircular
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HBubbleCircular)
    Q_PROPERTY(QColor foreground READ foreground WRITE setForeground)

public:
    explicit HBubbleCircular(QObject *parent = nullptr);

public:
    void initialize(QVariantMap param = QVariantMap()) override;
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

HE_END_NAMESPACE
