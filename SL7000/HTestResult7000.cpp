#include "HTestResult7000_p.h"
#include "HeCore/HAppContext.h"
#include "HeData/ITestData.h"
#include "HeData/HDataType.h"

HTestResult7000Private::HTestResult7000Private()
{
    testData = HAppContext::getContextPointer<ITestData>("ITestData");
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
    if (i < 0 || i >= d_ptr->polygon.size())
        return nullptr;
    return d_ptr->results.value(d_ptr->polygon.at(i), nullptr);
}

bool HTestResult7000::isEmpty()
{
    return d_ptr->results.isEmpty();
}

int HTestResult7000::size()
{
    return d_ptr->polygon.size();
}

void HTestResult7000::clear()
{
    if (isEmpty())
        return;
    qDeleteAll(d_ptr->results);
    d_ptr->results.clear();
    d_ptr->modified = true;
}

void HTestResult7000::update()
{
    auto point = d_ptr->testData->data("[电机定位]").toPoint();
    d_ptr->modified = true;
    if (d_ptr->results.contains(point))
        d_ptr->results.value(point)->setData(d_ptr->testData->cloneData());
    else
        d_ptr->results.insert(point, d_ptr->testData->clone());
}

int HTestResult7000::next(int index)
{
    auto size = d_ptr->polygon.size();
    for (int i = index + 1; i < size; i++)
    {
        auto data = at(i);
        if (data == nullptr || data->data("[品质]").toInt() != HQualityReport::Passing)
            return i;
    }
    return -1;
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
