#include "HCodecSL_p.h"

HE_COMMUNICATE_BEGIN_NAMESPACE

HCodecSLPrivate::HCodecSLPrivate()
{
    encrypts << true << false;
    checkCodes << true << true;
}

HCodecSL::HCodecSL() :
    HAbstractCodec(*new HCodecSLPrivate)
{
}

HCodecSL::HCodecSL(HCodecSLPrivate &p) :
    HAbstractCodec(p)
{
}

HCodecSL::~HCodecSL()
{
}

void HCodecSL::initialize(QVariantMap param)
{
    Q_D(HCodecSL);
    if (param.contains("encrypt"))
        setEncrypt(param.value("encrypt").value<QVector<bool>>());
    if (param.contains("checkCode"))
        setCheckCode(param.value("checkCode").value<QVector<bool>>());
}

QString HCodecSL::typeName()
{
    return "HCodecSL";
}

QVector<uchar> HCodecSL::preDecode(QVector<uchar> value)
{
    int n = value.size();
    if (isEncrypt(1))
        n += encryptSize(value);
    if (isCheckCode(1))
        n += 1;
    return QVector<uchar>(n);
}

QVector<uchar> HCodecSL::encode(QVector<uchar> value)
{
    if (isEncrypt(0))
        value = encrypt(value);
    if (isCheckCode(0))
        value << calcCheckCode(value);
    return value;
}

QVector<uchar> HCodecSL::decode(QVector<uchar> value)
{
    if (isCheckCode(1))
        value.takeLast();
    if (isEncrypt(1))
        value = decrypt(value);
    return value;
}

bool HCodecSL::check(QVector<uchar> value)
{
    auto code = value.takeLast();
    return code == calcCheckCode(value);
}

void HCodecSL::setEncrypt(QVector<bool> value)
{
    Q_D(HCodecSL);
    d->encrypts = value;
    if (d->encrypts.size() == 0)
        d->encrypts.append(false);
}

void HCodecSL::setCheckCode(QVector<bool> value)
{
    Q_D(HCodecSL);
    d->checkCodes = value;
    if (d->checkCodes.size() == 0)
        d->checkCodes.append(false);
}

bool HCodecSL::isEncrypt(int n)
{
    Q_D(HCodecSL);
    n = qBound(0, n, d->encrypts.size() - 1);
    return d->encrypts[n];
}

bool HCodecSL::isCheckCode(int n)
{
    Q_D(HCodecSL);
    n = qBound(0, n, d->checkCodes.size() - 1);
    return d->checkCodes[n];
}

int HCodecSL::encryptSize(QVector<uchar> value)
{
    Q_UNUSED(value)
    return 2;
    // return qCeil(value.size() / 7.0);
}

QVector<uchar> HCodecSL::encrypt(QVector<uchar> value)
{
    int n = value.size();
    int m = encryptSize(value);
    QVector<uchar> result(n + m);

    for (int i = 0; i < n; i++)
    {
        result[i] = (i == 0) ? value[i] | 0x80 : value[i] & 0x7F;
        result[n + i / 7] |= (value[i] & 0x80) >> (7 - (i % 7));
    }
    return result;
}

QVector<uchar> HCodecSL::decrypt(QVector<uchar> value)
{
    int n = value.size() - encryptSize(value);
    QVector<uchar> result(n);

    for (int i = 0; i < n; i++)
    {
        if ((value[n + i / 7] >> (i % 7)) % 2 == 0)
            result[i] = value[i] & 0x7F;
        else
            result[i] = value[i] | 0x80;
    }
    return result;
}

uchar HCodecSL::calcCheckCode(QVector<uchar> value)
{
    uint sum = 0;
    for (auto i : value)
        sum += i;
    return sum % 128;
}

HE_COMMUNICATE_END_NAMESPACE
