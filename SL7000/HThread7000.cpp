#include "HThread7000_p.h"



HThread7000::HThread7000(QObject *parent) :
    HAbstractThread(*new HThread7000Private, parent)
{
}

HThread7000::HThread7000(HThread7000Private &p, QObject *parent) :
    HAbstractThread(p, parent)
{
}

HThread7000::~HThread7000()
{
}


