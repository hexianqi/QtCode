#include "HXYDomain_p.h"

HXYDomain::HXYDomain(QObject *parent)
    : HAbstractDomain(*new HXYDomainPrivate, parent)
{
}

HXYDomain::HXYDomain(HXYDomainPrivate &p, QObject *parent)
    : HAbstractDomain(p, parent)
{
}


HXYDomain::~HXYDomain()
{
}

