#include "HTestResult7000_p.h"

HTestResult7000Private::HTestResult7000Private()
{
}

HTestResult7000::HTestResult7000(QObject *parent) :
    QObject(parent),
    d_ptr(new HTestResult7000Private)
{
}

HTestResult7000::~HTestResult7000()
{
    clear();
}

ITestData *HTestResult7000::at(int i)
{
    if (i < 0 || i >= d_ptr->results.size())
        return nullptr;
    return d_ptr->results.at(i);
}

bool HTestResult7000::isEmpty()
{
    return d_ptr->results.isEmpty();
}

int HTestResult7000::size()
{
    return d_ptr->results.size();
}

void HTestResult7000::clear()
{
    if (isEmpty())
        return;
    qDeleteAll(d_ptr->results);
    d_ptr->results.clear();
    d_ptr->modified = true;
}

void HTestResult7000::setPolygon(QPolygon value)
{
    if (d_ptr->polygon == value)
        return;
    d_ptr->polygon = value;
    clear();
}

void HTestResult7000::setModified(bool b)
{
    d_ptr->modified = b;
}
