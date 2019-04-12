/***************************************************************************************************
**      2019-04-08  HCodecSL    SL编码类。
***************************************************************************************************/

#ifndef HCODECSL_H
#define HCODECSL_H

#include "HAbstractCodec.h"

HE_COMMUNICATE_BEGIN_NAMESPACE

class HCodecSLPrivate;

class HCodecSL : public HAbstractCodec
{
    Q_DECLARE_PRIVATE(HCodecSL)

public:
    explicit HCodecSL();
    ~HCodecSL() override;

public:
    void initialize(QVariantMap param) override;
    QString typeName() override;

public:
    QVector<uchar> preDecode(QVector<uchar> value) override;
    QVector<uchar> encode(QVector<uchar> value) override;
    QVector<uchar> decode(QVector<uchar> value) override;
    bool check(QVector<uchar> value) override;

protected:
    HCodecSL(HCodecSLPrivate &);

protected:
    void setEncrypt(QVector<bool> value);
    void setCheckCode(QVector<bool> value);
    bool isEncrypt(int n);
    bool isCheckCode(int n);
    int encryptSize(QVector<uchar> value);
    QVector<uchar> encrypt(QVector<uchar> value);
    QVector<uchar> decrypt(QVector<uchar> value);
    uchar calcCheckCode(QVector<uchar> value);
};

HE_COMMUNICATE_END_NAMESPACE

#endif // HCODECSL_H
