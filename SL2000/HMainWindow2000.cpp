#include "HMainWindow2000_p.h"

HMainWindow2000Private::HMainWindow2000Private(HMainWindow2000 *q)
    : HMainWindowPrivate(q)
{
}

HMainWindow2000::HMainWindow2000(QWidget *parent)
    : HMainWindow(*new HMainWindow2000Private(this), parent)
{

}

HMainWindow2000::HMainWindow2000(HMainWindow2000Private &p, QWidget *parent)
    : HMainWindow(p, parent)
{
}

HMainWindow2000::~HMainWindow2000()
{
}

