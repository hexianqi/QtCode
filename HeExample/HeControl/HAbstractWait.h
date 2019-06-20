/***************************************************************************************************
**      2019-06-19  HAbstractWait
***************************************************************************************************/

#ifndef HABSTRACTWAIT_H
#define HABSTRACTWAIT_H

#include "IWait.h"

HE_CONTROL_BEGIN_NAMESPACE

class HAbstractWaitPrivate;

class HAbstractWait : public IWait
{
    Q_OBJECT

public:
    explicit HAbstractWait(QObject *parent = nullptr);
    ~HAbstractWait() override;

public:
    void draw(QPainter *, QVariantMap param = QVariantMap()) override;

protected:
    HAbstractWait(HAbstractWaitPrivate &p, QObject *parent = nullptr);

protected:
    QScopedPointer<HAbstractWaitPrivate> d_ptr;
};

HE_CONTROL_END_NAMESPACE

#endif // HABSTRACTWAIT_H
