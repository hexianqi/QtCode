#include "HModel2000_p.h"

HModel2000Private::HModel2000Private(HModel2000 *q)
    : HAbstractModelPrivate(q)
{
}

HModel2000::HModel2000(QObject *parent)
    : HAbstractModel(*new HModel2000Private(this), parent)
{
}

HModel2000::HModel2000(HModel2000Private &p, QObject *parent)
    : HAbstractModel(p, parent)
{
}

HModel2000::~HModel2000()
{
}

void HModel2000::initialize(QVariantMap /*param*/)
{
}

QString HModel2000::typeName()
{
    return "HModel2000";
}
