/***************************************************************************************************
**      2019-05-21  HSlDevice2 SL设备类（第2版）。
***************************************************************************************************/

#pragma once

#include "HAbstractDevice.h"

HE_COMMUNICATE_BEGIN_NAMESPACE

class HSlDevice2Private;

class HSlDevice2 : public HAbstractDevice
{
    Q_DECLARE_PRIVATE(HSlDevice2)

public:
    explicit HSlDevice2();
    ~HSlDevice2() override;

public:
    QString typeName() override;

public:
    bool setData(HActionType action, QVector<uchar> value, int delay = 0) override;
    bool getData(HActionType action, QVector<uchar> &value, int delay = 0) override;

protected:
    HSlDevice2(HSlDevice2Private &);

protected:
    bool setDataOnce(uchar cmd, QVector<uchar> value, int delay = 0);
    bool getDataOnce(int size, uchar cmd, uchar block, QVector<uchar> &value, int delay = 0);
    bool setDataBatch(QList<uchar> param, QVector<uchar> value, int delay = 0);
    bool getDataBatch(QList<uchar> param, QVector<uchar> &value, int delay = 0);
};

HE_COMMUNICATE_END_NAMESPACE
