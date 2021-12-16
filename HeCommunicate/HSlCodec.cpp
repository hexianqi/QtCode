#include "HSlCodec_p.h"
#include <QtCore/QVector>

HE_BEGIN_NAMESPACE

HSlCodecPrivate::HSlCodecPrivate()
{
    encrypts << true << false;
    checkCodes << true << true;
}

HSlCodec::HSlCodec() :
    HAbstractCodec(*new HSlCodecPrivate)
{
}

HSlCodec::HSlCodec(HSlCodecPrivate &p) :
    HAbstractCodec(p)
{
}

HSlCodec::~HSlCodec() = default;

void HSlCodec::initialize(QVariantMap param)
{
    if (param.contains("encrypt"))
        setEncrypt(param.value("encrypt").value<QVector<bool>>());
    if (param.contains("checkCode"))
        setCheckCode(param.value("checkCode").value<QVector<bool>>());
}

QString HSlCodec::typeName()
{
    return "HSlCodec";
}

QVector<uchar> HSlCodec::preDecode(QVector<uchar> value)
{
    int n = value.size();
    if (isEncrypt(1))
        n += encryptSize(value);
    if (isCheckCode(1))
        n += 1;
    return QVector<uchar>(n);
}

QVector<uchar> HSlCodec::encode(QVector<uchar> value)
{
    if (isEncrypt(0))
        value = encrypt(value);
    if (isCheckCode(0))
        value << calcCheckCode(value);
    return value;
}

QVector<uchar> HSlCodec::decode(QVector<uchar> value)
{
    if (isCheckCode(1))
        value.takeLast();
    if (isEncrypt(1))
        value = decrypt(value);
    return value;
}

bool HSlCodec::check(QVector<uchar> value)
{
    auto code = value.takeLast();
    return code == calcCheckCode(value);
}

void HSlCodec::setEncrypt(const QVector<bool> &value)
{
    Q_D(HSlCodec);
    d->encrypts = value;
    if (d->encrypts.isEmpty())
        d->encrypts.append(false);
}

void HSlCodec::setCheckCode(const QVector<bool> &value)
{
    Q_D(HSlCodec);
    d->checkCodes = value;
    if (d->checkCodes.isEmpty())
        d->checkCodes.append(false);
}

bool HSlCodec::isEncrypt(int n)
{
    Q_D(HSlCodec);
    n = qBound(0, n, d->encrypts.size() - 1);
    return d->encrypts[n];
}

bool HSlCodec::isCheckCode(int n)
{
    Q_D(HSlCodec);
    n = qBound(0, n, d->checkCodes.size() - 1);
    return d->checkCodes[n];
}

int HSlCodec::encryptSize(QVector<uchar> value)
{
    Q_UNUSED(value)
    return 2;
    // return qCeil(value.size() / 7.0);
}

QVector<uchar> HSlCodec::encrypt(QVector<uchar> value)
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

QVector<uchar> HSlCodec::decrypt(QVector<uchar> value)
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

uchar HSlCodec::calcCheckCode(QVector<uchar> value)
{
    uint sum = 0;
    for (auto i : value)
        sum += i;
    return sum % 128;
}

HE_END_NAMESPACE
