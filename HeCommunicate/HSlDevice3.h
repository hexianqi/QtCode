/***************************************************************************************************
**      2018-06-19  HSlCodecDevice SL设备类（带编码）。
***************************************************************************************************/

#pragma once

#include "HSlDevice1.h"

HE_BEGIN_NAMESPACE

class HSlDevice3Private;

class HSlDevice3 : public HSlDevice1
{
    Q_DECLARE_PRIVATE(HSlDevice3)

public:
    explicit HSlDevice3();
    ~HSlDevice3() override;

public:
    void initialize(QVariantMap param = QVariantMap()) override;
    QString typeName() override;

protected:
    void transport(QVector<uchar> &downData, QVector<uchar> &upData, int delay = 0) override;
};

HE_END_NAMESPACE
