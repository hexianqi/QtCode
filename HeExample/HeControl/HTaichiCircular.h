/***************************************************************************************************
**      2019-06-19  HTaichiCircular 太极。
***************************************************************************************************/

#ifndef HTAICHICIRCULAR_H
#define HTAICHICIRCULAR_H

#include "HAbstractCircular.h"
#include <QtGui/QColor>

HE_CONTROL_BEGIN_NAMESPACE

class HTaichiCircularPrivate;

class HTaichiCircular : public HAbstractCircular
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HTaichiCircular)
    Q_PROPERTY(QColor background READ background WRITE setBackground)
    Q_PROPERTY(QColor foreground READ foreground WRITE setForeground)

public:
    explicit HTaichiCircular(QObject *parent = nullptr);
    ~HTaichiCircular() override;

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
    HTaichiCircular(HTaichiCircularPrivate &p, QObject *parent = nullptr);
};

HE_CONTROL_END_NAMESPACE

#endif // HTAICHICIRCULAR_H
