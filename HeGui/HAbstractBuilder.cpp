#include "HAbstractBuilder_p.h"

HE_GUI_BEGIN_NAMESPACE

HAbstractBuilder::HAbstractBuilder(QObject *parent)
    : QObject(parent), d_ptr(new HAbstractBuilderPrivate)
{
}

HAbstractBuilder::HAbstractBuilder(HAbstractBuilderPrivate &p, QObject *parent)
    : QObject(parent), d_ptr(&p)
{
}

HAbstractBuilder::~HAbstractBuilder()
{
}

HE_GUI_END_NAMESPACE
