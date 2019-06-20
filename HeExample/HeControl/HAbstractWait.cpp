#include "HAbstractWait_p.h"
#include <QtGui/QPainter>

HE_CONTROL_BEGIN_NAMESPACE

HAbstractWait::HAbstractWait(QObject *parent) :
    IWait(parent),
    d_ptr(new HAbstractWaitPrivate)
{
}

HAbstractWait::HAbstractWait(HAbstractWaitPrivate &p, QObject *parent) :
    IWait(parent),
    d_ptr(&p)
{
}

HAbstractWait::~HAbstractWait()
{
}

void HAbstractWait::draw(QPainter *painter, QVariantMap param)
{
    auto w = param.value("width", 100).toInt();
    auto h = param.value("height", 100).toInt();
    auto side = qMin(w, h);
    painter->translate(w / 2, h / 2);
    painter->scale(side / 100.0, side / 100.0);
}

HE_CONTROL_END_NAMESPACE
