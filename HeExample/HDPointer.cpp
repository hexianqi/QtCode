#include "HDPointer.h"
#include "HDPointer_p.h"

HE_EXAMPLE_BEGIN_NAMESPACE

void HDPointerPrivate::init()
{
    Q_Q(HDPointer);

    da = 10;
    q->test();
}

HDPointer::HDPointer(QObject *parent)
    : QObject(*new HDPointerPrivate, parent)
{
    Q_D(HDPointer);
    d->init();
}

HDPointer::HDPointer(HDPointerPrivate &p, QObject *parent)
    : QObject(p, parent)
{
    Q_D(HDPointer);
    d->init();
}

HDPointer::~HDPointer()
{
}

void HDPointer::test()
{

}

HE_EXAMPLE_END_NAMESPACE
