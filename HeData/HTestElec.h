/***************************************************************************************************
**      2019-10-21  HTestElec
***************************************************************************************************/

#ifndef HTESTELEC_H
#define HTESTELEC_H

#include "HDataType.h"
#include "HTestData.h"

HE_DATA_BEGIN_NAMESPACE

class HTestElecPrivate;

class HTestElec : public HTestData
{
    Q_DECLARE_PRIVATE(HTestElec)

public:
    explicit HTestElec();

public:
    QString typeName() override;

public:
    bool setCalibrate(void *) override;
    void setData(QString type, QVariant value) override;

protected:
    HTestElec(HTestElecPrivate &);

protected:
    void setModule(int value);
    void setGears(HElecType type, int value);
    void setParam(HElecType type, double value);
    void calcRelation(HElecType type);
};

HE_DATA_END_NAMESPACE

#endif // HTESTELEC_H
