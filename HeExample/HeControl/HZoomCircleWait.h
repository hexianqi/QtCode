/***************************************************************************************************
**      2019-06-20  HZoomCircleWait 圆缩放
***************************************************************************************************/

#ifndef HZOOMCIRCLEWAIT_H
#define HZOOMCIRCLEWAIT_H

#include "HAbstractWait.h"
#include <QtGui/QColor>

HE_CONTROL_BEGIN_NAMESPACE

class HZoomCircleWaitPrivate;

class HZoomCircleWait : public HAbstractWait
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HZoomCircleWait)
    Q_PROPERTY(QColor foreground READ foreground WRITE setForeground)
    Q_PROPERTY(int minimum READ minimum WRITE setMinimum)
    Q_PROPERTY(bool bounce READ bounce WRITE setBounce)

public:
    explicit HZoomCircleWait(QObject *parent = nullptr);
    ~HZoomCircleWait() override;

public:
    void initialize(QVariantMap param) override;
    QString typeName() override;

public:
    void draw(QPainter *, QVariantMap param = QVariantMap()) override;

public:
    QColor foreground() const;
    double minimum() const;
    bool bounce() const;

public slots:
    void setForeground(const QColor &value);
    void setMinimum(int value);
    void setBounce(bool b);

protected:
    HZoomCircleWait(HZoomCircleWaitPrivate &p, QObject *parent = nullptr);

protected:
    double calcRaidous(int value);
};

HE_CONTROL_END_NAMESPACE

#endif // HZOOMCIRCLEWAIT_H
