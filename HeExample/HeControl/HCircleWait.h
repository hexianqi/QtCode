/***************************************************************************************************
**      2019-06-19  HCircleWait 圈状
***************************************************************************************************/

#ifndef HCIRCLEWAIT_H
#define HCIRCLEWAIT_H

#include "HAbstractWait.h"
#include <QtGui/QColor>

HE_CONTROL_BEGIN_NAMESPACE

class HCircleWaitPrivate;

class HCircleWait : public HAbstractWait
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HCircleWait)
    Q_PROPERTY(QColor foreground READ foreground WRITE setForeground)

public:
    explicit HCircleWait(QObject *parent = nullptr);
    ~HCircleWait() override;

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
    HCircleWait(HCircleWaitPrivate &p, QObject *parent = nullptr);
};

HE_CONTROL_END_NAMESPACE

#endif // HCIRCLEWAIT_H
