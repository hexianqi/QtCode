#include "HControllerHelper.h"
#include "HeData/ITestData.h"
#include "HeCommunicate/IProtocol.h"
#include <QtCore/QVector>

HE_BEGIN_NAMESPACE

void HControllerHelper::multGetSpectrum(IProtocol *protocol, ITestData *testData, int times)
{
    int i,j;
    QVector<double> sample1, sample2;

    times = qMin(1, times);
    for (i = 0; i < times; i++)
    {
        protocol->getData(ACT_GET_SPECTRUM, sample2);
        if (sample1.size() < sample2.size())
            sample1.resize(sample2.size());
        for (j = 0; j < sample2.size(); j++)
            sample1[j] += 1.0 * sample2.at(j) / times;
    }
    testData->setData("[光谱采样值]", QVariant::fromValue(sample1));
}

HE_END_NAMESPACE
