/***************************************************************************************************
**      2019-05-21  HSlDevice2 SL设备类（第2版）。
***************************************************************************************************/

#ifndef HSLDEVICE2_H
#define HSLDEVICE2_H

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
    HErrorType setData(HActionType action, QVector<uchar> value, int delay = 0) override;
    HErrorType getData(HActionType action, QVector<uchar> &value, int delay = 0) override;

protected:
    HSlDevice2(HSlDevice2Private &);

protected:
    HErrorType setDataOnce(uchar cmd, QVector<uchar> value, int delay = 0);
    HErrorType getDataOnce(int size, uchar cmd, uchar block, QVector<uchar> &value, int delay = 0);
    HErrorType setDataBatch(QList<uchar> param, QVector<uchar> value, int delay = 0);
    HErrorType getDataBatch(QList<uchar> param, QVector<uchar> &value, int delay = 0);
};

HE_COMMUNICATE_END_NAMESPACE

#endif // HSLDEVICE2_H
