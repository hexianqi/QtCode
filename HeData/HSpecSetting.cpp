#include "HSpecSetting_p.h"
#include "HDataHelper.h"
#include "HeCore/HCoreHelper.h"
#include "HeAlgorithm/HInterp.h"
#include "HeAlgorithm/HMath.h"
#include "HeAlgorithm/HSpecHelper.h"
#include <QtCore/QDataStream>

HE_BEGIN_NAMESPACE

HSpecSetting::HSpecSetting() :
    HAbstractDataItem(*new HSpecSettingPrivate)
{
    restoreDefault();
}

HSpecSetting::HSpecSetting(HSpecSettingPrivate &p) :
    HAbstractDataItem(p)
{
}

QString HSpecSetting::typeName()
{
    return "HSpecSetting";
}

void HSpecSetting::readContent(QDataStream &s)
{
    Q_D(HSpecSetting);
    quint32 version;
    QVariantMap data;
    s >> version;
    s >> data;
    d->datas = HCoreHelper::unite(d->datas, data);
}

void HSpecSetting::writeContent(QDataStream &s)
{
    Q_D(HSpecSetting);
    s << quint32(1);
    s << d->datas;
}

QVector<uchar> HSpecSetting::toBinaryData()
{
    auto pels = data("[光谱保留像元]").toPoint();
    auto times = data("[光谱平滑次数]").toInt();
    auto range = data("[光谱平滑范围]").toInt();
    auto frame = data("[光谱平滑帧数]").toInt();
    auto tc = quint16(data("[标准色温]").toDouble() * 10);
    auto r =  QVector<uchar>() << HDataHelper::writeUInt16(0)  // 大小
                               << HDataHelper::writeUInt16(1)  // 版本
                               << HDataHelper::writeUInt16(quint16(pels.x()))
                               << HDataHelper::writeUInt16(quint16(pels.y()))
                               << HDataHelper::writeUInt16(quint16(times))
                               << HDataHelper::writeUInt16(quint16(range))
                               << HDataHelper::writeUInt16(quint16(frame))
                               << HDataHelper::writeUInt16(tc);
    r[0] = uchar(r.size() / 256);
    r[1] = uchar(r.size() % 256);
    return r;
}

bool HSpecSetting::fromBinaryData(const QVector<uchar> &data, int &pos)
{
    int version = 0;
    if (!HDataHelper::checkHead(data, pos, version))
        return false;

    auto x = HDataHelper::readUInt16(data, pos);
    auto y = HDataHelper::readUInt16(data, pos);
    setData("[光谱保留像元]", QPoint(x, y));
    setData("[光谱平滑次数]", HDataHelper::readUInt16(data, pos));
    setData("[光谱平滑范围]", HDataHelper::readUInt16(data, pos));
    setData("[光谱平滑帧数]", HDataHelper::readUInt16(data, pos));
    setData("[标准色温]", HDataHelper::readUInt16(data, pos) / 10.0);
    return true;
}

void HSpecSetting::restoreDefault()
{
    setData("[标准色温]", 2855.61);
    setData("[积分时间范围]", QPointF(0.0, 500.0));
    setData("[光谱采样范围]", QPointF(6500.0, 64000.0));
    setData("[光谱波长范围]", QPointF(380.0, 780.0));
    setData("[光谱波长间隔]", 0.1);
    setData("[光谱平均次数]", 1);
    setData("[光谱采样延时]", 0);
    setData("[光谱保留像元]", QPoint(15, 32));
    setData("[光谱固定暗底]", 0.0);
    setData("[光谱左右暗底]", 0.0);
    setData("[光谱平滑帧数]", 1);
    setData("[光谱平滑次数]", 2);
    setData("[光谱平滑范围]", 2);
    setData("[光合自动查找波段]", false);
    setData("[光合蓝光范围]", QPointF(380.0, 450.0));
    setData("[光合荧光范围]", QPointF(450.0, 780.0));
}

QVariantMap HSpecSetting::testParam()
{
    QVariantMap param;
    auto list = QStringList() << "[光谱平均次数]" << "[光谱采样延时]" << "[光谱波长范围]";
    for (const auto &s : list)
        param.insert(s, data(s));
    return param;
}

QVariantMap HSpecSetting::calcSynthetic(QPolygonF energy, double k)
{
    QVariantMap result;
    auto blue = data("[光合蓝光范围]").toPointF();
    auto yellow = data("[光合荧光范围]").toPointF();
    if (data("[光合自动查找波段]").toBool() || blue.isNull() || yellow.isNull())
    {
        blue = QPointF(380.0, 500.0);
        yellow = QPointF(500.0, 780.0);
    }

    auto sumBlue = 0.0;
    auto sumYellow = 0.0;
    auto sum380_780 = 0.0;
    auto sum400_700 = 0.0;
    auto sum700_800 = 0.0;
    auto prf = 0.0;
    for (auto point : energy)
    {
        if (point.x() >= 380 && point.x() <= 780)
            sum380_780 += point.y() * point.x();
        if (point.x() >= 400 && point.x() <= 700)
        {
            sum400_700 += point.y() * point.x();
            prf += point.y();
        }
        if (point.x() >= 700 && point.x() <= 800)
            sum700_800 += point.y() * point.x();
        if (point.x() >= blue.x() && point.x() <= blue.y())
            sumBlue += point.y();
        if (point.x() >= yellow.x() && point.x() <= yellow.y())
            sumYellow += point.y();
    }
    result.insert("[光量子(380-780)]",  k * sum380_780 / 119.8);
    result.insert("[光量子(400-700)]",  k * sum400_700 / 119.8);
    result.insert("[光量子(700-800)]",  k * sum700_800 / 119.8);
    result.insert("[光合光量子通量]",   k * sum400_700 / 119.8);
    result.insert("[光合光子通量效率]", k * sum400_700 / 119.8);
    result.insert("[光合有效辐射通量]", k * prf * 1000);
    result.insert("[荧光效能]",         k * sumYellow);
    result.insert("[荧光蓝光比]",       qFuzzyIsNull(sumBlue) ? 0.0 : sumYellow / sumBlue);
    return result;
}

int HSpecSetting::calcCommWaitTime(double &value)
{
    auto range = data("[积分时间范围]").toPointF();
    auto times = data("[光谱平均次数]").toInt();
    value = qBound(range.x(), value, range.y());
    return ceil(value * times);
}

int HSpecSetting::checkIntegralTime(double value)
{
    auto range = data("[积分时间范围]").toPointF();
    if (value < range.x())
        return -2;
    if (value > range.y())
        return 2;
    if (qFuzzyCompare(value, range.x()))
        return -1;
    if (qFuzzyCompare(value, range.y()))
        return 1;
    return 0;
}

int HSpecSetting::checkFrameOverflow(int size)
{
    auto n = data("[光谱平滑帧数]").toInt();
    if (size < n)
        return -1;
    if (size > n)
        return 1;
    return 0;
}

int HSpecSetting::checkSampleOverflow(double value)
{
    auto range = data("[光谱采样范围]").toPointF();
    if (value < range.x())
        return -1;
    if (value > range.y())
        return 1;
    return 0;
}

QVector<double> HSpecSetting::dealBotton(QVector<double> value)
{
    int i;
    auto size = value.size();
    auto pels = data("[光谱保留像元]").toPoint();
    auto fixup = data("[光谱固定暗底]").toDouble();
    auto diff = data("[光谱左右暗底]").toDouble();
    auto avgbase = 0.0;

    for (i = pels.x(); i <= pels.y() && i < size; i++)
        avgbase += value[i];
    avgbase /= pels.y() - pels.x() + 1;

    for (i = 0; i < size; i++)
        value[i] = value[i] - avgbase + fixup + i * diff / size;

    return value;
}

QVector<double> HSpecSetting::smoothCurve(QVector<double> value)
{
    QVector<double> temp;
    auto size = value.size();
    auto times = data("[光谱平滑次数]").toInt();
    auto range = data("[光谱平滑范围]").toInt();
    temp.resize(size);
    for (int k = 0; k < times; k++)
    {
        for (int i = 0; i < size; i++)
        {
            auto avgbase = value[i];
            for (int j = 1; j <= range; j++)
            {
                auto m = qMax(i - j, 0);
                auto n = qMin(i + j, size - 1);
                avgbase += value[m] + value[n];
            }
            temp[i] = avgbase / (2 * range + 1);
        }
        value = temp;
    }
    return value;
}

QPolygonF HSpecSetting::interpEnergy(QPolygonF value, double offset)
{
    auto range = data("[光谱波长范围]").toPointF();
    auto interval = data("[光谱波长间隔]").toDouble();
    for (int i = 0; i < value.size(); i++)
        value[i].ry() *= calcEnergy(value[i].x(), offset);
    return HMath::interpolate(value, range.x(), range.y(), interval);
//    return HInterp::eval(value, range.x(), range.y(), interval, HInterpType::Cspline);
}

double HSpecSetting::calcEnergy(double wave, double offset)
{
    auto tc = data("[标准色温]").toDouble() + offset;
    return HSpecHelper::planck(tc, wave);
}

HE_END_NAMESPACE
