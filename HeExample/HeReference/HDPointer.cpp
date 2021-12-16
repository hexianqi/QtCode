#include "HDPointer_p.h"

HE_BEGIN_NAMESPACE

void HDPointerPrivate::init()
{
    Q_Q(HDPointer);
    da = 10;
    q->test();
}

HDPointer::HDPointer(QObject *parent) :
    QObject(*new HDPointerPrivate, parent)
{
    Q_D(HDPointer);
    d->init();
}

HDPointer::HDPointer(HDPointerPrivate &p, QObject *parent) :
    QObject(p, parent)
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

HE_END_NAMESPACE
