#include "HAbstractCircular_p.h"
#include <QtGui/QPainter>

HE_CONTROL_BEGIN_NAMESPACE

HAbstractCircular::HAbstractCircular(QObject *parent) :
    ICircular(parent),
    d_ptr(new HAbstractCircularPrivate)
{
}

HAbstractCircular::HAbstractCircular(HAbstractCircularPrivate &p, QObject *parent) :
    ICircular(parent),
    d_ptr(&p)
{
}

HAbstractCircular::~HAbstractCircular() = default;

void HAbstractCircular::initialize(QVariantMap /*param*/)
{
}

void HAbstractCircular::draw(QPainter *painter, double /*factor*/, QVariantMap param)
{
    auto w = param.value("width", 100).toInt();
    auto h = param.value("height", 100).toInt();
    auto side = qMin(w, h);
    painter->translate(w / 2.0, h / 2.0);
    painter->scale(side / 100.0, side / 100.0);
}

HE_CONTROL_END_NAMESPACE
