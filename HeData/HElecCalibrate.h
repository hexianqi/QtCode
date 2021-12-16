/***************************************************************************************************
**      2019-10-15  HElecCalibrate 电校准数据类。
***************************************************************************************************/

#pragma once

#include "IElecCalibrate.h"

HE_BEGIN_NAMESPACE

class HElecCalibratePrivate;

class HElecCalibrate : public IElecCalibrate
{
public:
    explicit HElecCalibrate();
    ~HElecCalibrate();

public:
    void initialize(QVariantMap param = QVariantMap()) override;
    QString typeName() override;

public:
    void readContent(QDataStream &) override;
    void writeContent(QDataStream &) override;

public:
    void setItemCollection(HElecType type, IElecCalibrateItemCollection *) override;
    IElecCalibrateItemCollection *itemCollection(HElecType type) override;
    IElecCalibrateItem *item(HElecType type, int index = 0) override;
    double toFiction(double value, HElecType type, int index = 0) override;
    double toReal(double value, HElecType type, int index = 0) override;
    QString toString(HElecType type) override;

protected:
    HElecCalibrate(HElecCalibratePrivate &);

protected:
    QScopedPointer<HElecCalibratePrivate> d_ptr;
};

HE_END_NAMESPACE
