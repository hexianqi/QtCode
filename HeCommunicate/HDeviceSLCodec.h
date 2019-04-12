/***************************************************************************************************
**      2018-06-19  HDeviceSLCodec SL设备类（带编码）。
***************************************************************************************************/

#ifndef HDEVICESLCODEC_H
#define HDEVICESLCODEC_H

#include "HDeviceSL.h"

HE_COMMUNICATE_BEGIN_NAMESPACE

class HDeviceSLCodecPrivate;

class HDeviceSLCodec : public HDeviceSL
{
    Q_DECLARE_PRIVATE(HDeviceSLCodec)

public:
    explicit HDeviceSLCodec();
    ~HDeviceSLCodec() override;

public:
    void initialize(QVariantMap param) override;
    QString typeName() override;

protected:
    virtual HErrorType transport(QVector<uchar> &downData, QVector<uchar> &upData, int delay = 0);
};

HE_COMMUNICATE_END_NAMESPACE

#endif // HDEVICESLCODEC_H
