/***************************************************************************************************
**      2019-04-08  HSlCodec Sl编码类。
***************************************************************************************************/

#pragma once

#include "HAbstractCodec.h"

HE_BEGIN_NAMESPACE

class HSlCodecPrivate;

class HSlCodec : public HAbstractCodec
{
    Q_DECLARE_PRIVATE(HSlCodec)

public:
    explicit HSlCodec();
    ~HSlCodec() override;

public:
    void initialize(QVariantMap param = QVariantMap()) override;
    QString typeName() override;

public:
    QVector<uchar> preDecode(QVector<uchar> value) override;
    QVector<uchar> encode(QVector<uchar> value) override;
    QVector<uchar> decode(QVector<uchar> value) override;
    bool check(QVector<uchar> value) override;

protected:
    HSlCodec(HSlCodecPrivate &);

protected:
    void setEncrypt(const QVector<bool> &value);
    void setCheckCode(const QVector<bool> &value);
    bool isEncrypt(int n);
    bool isCheckCode(int n);
    int encryptSize(QVector<uchar> value);
    QVector<uchar> encrypt(QVector<uchar> value);
    QVector<uchar> decrypt(QVector<uchar> value);
    uchar calcCheckCode(QVector<uchar> value);
};

HE_END_NAMESPACE
