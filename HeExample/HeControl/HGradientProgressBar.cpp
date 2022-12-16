#include "HGradientProgressBar_p.h"

HE_BEGIN_NAMESPACE

HGradientProgressBar::HGradientProgressBar(QWidget *parent) :
    QProgressBar(parent),
    d_ptr(new HGradientProgressBarPrivate)
{
}

HGradientProgressBar::HGradientProgressBar(HGradientProgressBarPrivate &p, QWidget *parent) :
    QProgressBar(parent),
    d_ptr(&p)
{
}

HGradientProgressBar::~HGradientProgressBar()
{
}

HE_END_NAMESPACE
