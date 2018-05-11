#ifndef ITESTSPEC_H
#define ITESTSPEC_H

#include "ITestData.h"

HE_CONTROLLER_BEGIN_NAMESPACE

class ITestSpec : public ITestData
{

public:
    virtual bool setSample(QVector<double> value, bool avg = false) = 0;
    virtual void clearQueue() = 0;


};

HE_CONTROLLER_END_NAMESPACE

#endif // ITESTSPECTRUM_H
