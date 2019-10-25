/***************************************************************************************************
**      2019-10-21  HTestElec
***************************************************************************************************/

#ifndef HTESTELEC_H
#define HTESTELEC_H

#include "ITestElec.h"

HE_DATA_BEGIN_NAMESPACE

class HTestElecPrivate;

class HTestElec : public ITestElec
{
    Q_DECLARE_PRIVATE(HTestElec)

public:
    explicit HTestElec();
    ~HTestElec() override;

public:
    QString typeName() override;

public:
    bool setCalibrate(IElecCalibrateCollection *) override;
    void setModule(int value) override;
    void setModule(QString value) override;
    void setGears(HElecType type, int value) override;
    void setParam(HElecType type, double value) override;
    void setSample(QVector<int> value) override;

protected:
    HTestElec(HTestElecPrivate &);

protected:
    int gears(HElecType type);
};

HE_DATA_END_NAMESPACE

#endif // HTESTELEC_H
