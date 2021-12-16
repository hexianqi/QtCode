/***************************************************************************************************
**      2019-06-20  HLineCircular 线状
***************************************************************************************************/

#pragma once

#include "HAbstractCircular.h"
#include <QtGui/QColor>

HE_BEGIN_NAMESPACE

class HLineCircularPrivate;

class HLineCircular : public HAbstractCircular
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HLineCircular)
    Q_PROPERTY(QColor foreground READ foreground WRITE setForeground)

public:
    explicit HLineCircular(QObject *parent = nullptr);

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
    HLineCircular(HLineCircularPrivate &p, QObject *parent = nullptr);
};

HE_END_NAMESPACE
