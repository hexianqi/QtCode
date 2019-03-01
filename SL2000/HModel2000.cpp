#include "HModel2000_p.h"
#include <QDebug>

HModel2000Private::HModel2000Private()
{
}

HModel2000::HModel2000(QObject *parent)
    : HAbstractModel(*new HModel2000Private, parent)
{
}

HModel2000::HModel2000(HModel2000Private &p, QObject *parent)
    : HAbstractModel(p, parent)
{
}

HModel2000::~HModel2000()
{
    qDebug() << __func__;
}

void HModel2000::initialize(QVariantMap /*param*/)
{
}

QString HModel2000::typeName()
{
    return "HModel2000";
}
