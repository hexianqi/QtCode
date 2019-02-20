#include "HSpecSetting_p.h"
#include "HeAlgorithm/HInterp.h"
#include "HeAlgorithm/HSpectrumHelper.h"
#include <QDataStream>

HE_ALGORITHM_USE_NAMESPACE

HE_DATA_BEGIN_NAMESPACE

HSpecSetting::HSpecSetting()
    : HAbstractCalibrateItem(*new HSpecSettingPrivate)
{
    restoreDefault();
}

HSpecSetting::HSpecSetting(HSpecSettingPrivate &p)
    : HAbstractCalibrateItem(p)
{
    restoreDefault();
}

HSpecSetting::~HSpecSetting()
{
}

void HSpecSetting::restoreDefault()
{
    Q_D(HSpecSetting);
    setData("[光谱平均次数]", 1);
    setData("[光谱采样延时]", 0);
    setData("[积分时间范围]", QPointF(0.0, 500.0));
    setData("[光谱平滑帧数]", 1);
    setData("[光谱保留像元]", QPoint(15, 32));
    setData("[光谱固定暗底]", 0.0);
    setData("[光谱左右暗底差]", 0.0);
    setData("[光谱平滑次数]", 2);
    setData("[光谱平滑范围]", 2);
    setData("[光谱采样范围]", QPointF(6500.0, 64000.0));
    setData("[光谱波长范围]", QPointF(380.0, 780.0));
    setData("[光谱波长间隔]", 0.1);
    setData("[光谱屏蔽波长范围]", QPointF(0.0, 0.0));
    setData("[标准色温]", 2855.61);
    d->isUsePlanck = true;
    d->isUseShield = false;
}

void HSpecSetting::readContent(QDataStream &s)
{
    Q_D(HSpecSetting);
    quint32 version;
    s >> version;
    s >> d->datas;
    s >> d->isUsePlanck;
    s >> d->isUseShield;
    s >> d->stdEnergy;
}

void HSpecSetting::writeContent(QDataStream &s)
{
    Q_D(HSpecSetting);
    s << quint32(1);
    s << d->datas;
    s << d->isUsePlanck;
    s << d->isUseShield;
    s << d->stdEnergy;
}

QVariantMap HSpecSetting::testParam()
{
    QVariantMap param;
    auto list = QStringList() << "[光谱平均次数]" << "[光谱采样延时]";
    for (auto s : list)
        param.insert(s, data(s));
    return param;
}

int HSpecSetting::calcCommWaitTime(double &value)
{
    auto range = data("[积分时间范围]").toPointF();
    auto times = data("[光谱平均次数]").toInt();
    value = qBound(range.x(), value, range.y());
    return value * times + 50;
}

bool HSpecSetting::isOverFrame(int size)
{
    return size >= data("[光谱平滑帧数]").toInt();
}

int HSpecSetting::checkOverflow(double value)
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
    auto size = value.size();
    auto pels = data("[光谱保留像元]").toPoint();
    auto fixup = data("[光谱固定暗底]").toDouble();
    auto diff = data("[光谱左右暗底差]").toDouble();
    auto avgbase = 0.0;

    for (int i = pels.x(); i <= pels.y() && i < size; i++)
        avgbase += value[i];
    avgbase /= pels.y() - pels.x() + 1;

    for (int i = 0; i < size; i++)
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
            auto avgbase = 0.0;
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

QPolygonF HSpecSetting::interpEnergy(QPolygonF value)
{
    auto range = data("[光谱波长范围]").toPointF();
    auto interval = data("[光谱波长间隔]").toDouble();
    for (int i = 0; i < value.size(); i++)
        value[i].ry() *= calcEnergy(value[i].x());
    return HInterp::eval(value, range.x(), range.y(), interval, HInterpType::Cspline);
}

QPolygonF HSpecSetting::shieldEnergy(QPolygonF value)
{
    Q_D(HSpecSetting);
    if (!d->isUseShield)
        return value;

    QPolygonF result;
    auto range = data("[光谱屏蔽波长范围]").toPointF();
    for (auto p : value)
    {
        auto x = p.x();
        auto y = (x >= range.x() && x <= range.y()) ? 0 : p.y();
        result.append(QPointF(x ,y));
    }
    return result;
}

double HSpecSetting::calcEnergy(double wave)
{
    Q_D(HSpecSetting);
    auto tc = data("[标准色温]").toDouble();
    if (d->isUsePlanck || d->stdEnergy.size() < 2)
        return HSpectrumHelper::planck(wave, tc);
    return HInterp::eval(d->stdEnergy, wave, HInterpType::Cspline);
}

HE_DATA_END_NAMESPACE
