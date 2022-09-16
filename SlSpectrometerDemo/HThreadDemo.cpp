#include "HThreadDemo_p.h"

HThreadDemo::HThreadDemo(QObject *parent) :
    HAbstractThread(*new HThreadDemoPrivate, parent)
{
}

HThreadDemo::~HThreadDemo()
{
}


