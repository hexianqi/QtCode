#include "HTestResult1000RGB_p.h"
#include "HeCore/HAppContext.h"
#include "HeData/ITestData.h"

HTestResult1000RGBPrivate::HTestResult1000RGBPrivate()
{
    testData = HAppContext::getContextPointer<ITestData>("ITestData");
}

HTestResult1000RGB::HTestResult1000RGB(QObject *parent) :
    QObject(parent),
    d_ptr(new HTestResult1000RGBPrivate)
{
}

HTestResult1000RGB::~HTestResult1000RGB()
{
    clear();
}

bool HTestResult1000RGB::isEmpty(int key)
{
    return !d_ptr->results.contains(key) || d_ptr->results.value(key).isEmpty();
}

void HTestResult1000RGB::clear()
{
    for (auto key : d_ptr->results.keys())
    {
        if (isEmpty(key))
            continue;
        qDeleteAll(d_ptr->results[key]);
        d_ptr->results[key].clear();
    }
}

void HTestResult1000RGB::update(bool append)
{
    auto k = d_ptr->testData->data("[TypeId]").toInt();
    auto r = d_ptr->results[k];
    if (append || isEmpty(k))
        r.append(d_ptr->testData->clone());
    else
        r.last()->setData(d_ptr->testData->cloneData());
}
