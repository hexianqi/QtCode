/***************************************************************************************************
**      2018-06-19  HSpecSetting 光谱配置数据类。
***************************************************************************************************/

#ifndef HSPECSETTING_H
#define HSPECSETTING_H

#include "HAbstractCalibrateItem.h"

HE_DATA_BEGIN_NAMESPACE

class HSpecSettingPrivate;

class HSpecSetting : public HAbstractCalibrateItem
{
    Q_DECLARE_PRIVATE(HSpecSetting)

public:
    explicit HSpecSetting();
    ~HSpecSetting();

public:
    virtual void restoreDefault() override;

public:
    virtual void readContent(QDataStream &) override;
    virtual void writeContent(QDataStream &) override;

public:
    // 对外参数
    QVariantMap testParam();
    // 计算通讯等待时间
    int calcCommWaitTime(double &value);
    // 是否超过帧数
    bool isOverFrame(int size);
    // 是否数据溢出
    int checkOverflow(double value);
    // 扣暗底
    QVector<double> dealBotton(QVector<double> value);
    // 平滑数据
    QVector<double> smoothCurve(QVector<double> value);
    // 计算并插值光谱能量，value是波长和采样值与标准曲线比值的集合
    QPolygonF interpEnergy(QPolygonF value);
    // 屏蔽能量
    QPolygonF shieldEnergy(QPolygonF value);

protected:
    HSpecSetting(HSpecSettingPrivate &p);

protected:
    double calcEnergy(double wave);
};

HE_DATA_END_NAMESPACE

#endif // HSPECSETTING_H
