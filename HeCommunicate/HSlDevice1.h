/***************************************************************************************************
**      2019-04-08  HSlDevice SL设备类。
***************************************************************************************************/

#pragma once

#include "HAbstractDevice.h"

HE_BEGIN_NAMESPACE

class HSlDevice1Private;

class HSlDevice1 : public HAbstractDevice
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HSlDevice1)

public:
    explicit HSlDevice1(QObject *parent = nullptr);
    ~HSlDevice1() override;

public:
    QString typeName() override;

public:
    bool setData(HActionType action, QVector<uchar> value, int delay = 0) override;
    bool getData(HActionType action, QVector<uchar> &value, int delay = 0) override;

protected:
    HSlDevice1(HSlDevice1Private &, QObject *parent = nullptr);

protected:
    virtual bool checkData(QVector<uchar> value, uchar cmd1, uchar cmd2);
};

HE_END_NAMESPACE
