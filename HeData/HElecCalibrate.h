/***************************************************************************************************
**      2019-10-15  HElecCalibrate 电校准数据类。
***************************************************************************************************/

#ifndef HELECCALIBRATE_H
#define HELECCALIBRATE_H

#include "IElecCalibrate.h"

HE_DATA_BEGIN_NAMESPACE

class HElecCalibratePrivate;

class HElecCalibrate : public IElecCalibrate
{
public:
    explicit HElecCalibrate();
    virtual ~HElecCalibrate();

public:
    void initialize(QVariantMap param) override;
    QString typeName() override;

public:
    void readContent(QDataStream &) override;
    void writeContent(QDataStream &) override;

public:
    void setItemCollection(ElecType type, IElecCalibrateItemCollection *) override;
    IElecCalibrateItemCollection *itemCollection(ElecType type) override;
    IElecCalibrateItem *item(ElecType type, int index = 0) override;
    double toFiction(double value, ElecType type, int index = 0) override;
    double toReal(double value, ElecType type, int index = 0) override;
    QString toString(ElecType type) override;

protected:
    HElecCalibrate(HElecCalibratePrivate &);

protected:


protected:
    QScopedPointer<HElecCalibratePrivate> d_ptr;
};

HE_DATA_END_NAMESPACE

#endif // HELECCALIBRATE_H
