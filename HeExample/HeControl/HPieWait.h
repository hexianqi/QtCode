/***************************************************************************************************
**      2019-06-20  HPieWait 饼状
***************************************************************************************************/

#ifndef HPIEWAIT_H
#define HPIEWAIT_H

#include "HAbstractWait.h"
#include <QtGui/QColor>

HE_CONTROL_BEGIN_NAMESPACE

class HPieWaitPrivate;

class HPieWait : public HAbstractWait
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HPieWait)
    Q_PROPERTY(QColor background READ background WRITE setBackground)
    Q_PROPERTY(QColor foreground READ foreground WRITE setForeground)
    Q_PROPERTY(int spanAngle READ spanAngle WRITE setSpanAngle)

public:
    explicit HPieWait(QObject *parent = nullptr);
    ~HPieWait() override;

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
    HPieWait(HPieWaitPrivate &p, QObject *parent = nullptr);
};

HE_CONTROL_END_NAMESPACE

#endif // HPIEWAIT_H
