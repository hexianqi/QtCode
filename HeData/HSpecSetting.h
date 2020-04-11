/***************************************************************************************************
**      2018-06-19  HSpecSetting 光谱配置数据类。
***************************************************************************************************/

#ifndef HSPECSETTING_H
#define HSPECSETTING_H

#include "HAbstractDataItem.h"

HE_DATA_BEGIN_NAMESPACE

class HSpecSettingPrivate;

class HE_DATA_EXPORT HSpecSetting : public HAbstractDataItem
{
    Q_DECLARE_PRIVATE(HSpecSetting)

public:
    explicit HSpecSetting();

public:
    QString typeName() override;

public:
    void readContent(QDataStream &) override;
    void writeContent(QDataStream &) override;
    QVector<uchar> toBinaryData();
    bool fromBinaryData(const QVector<uchar> &data, int &pos);

public:
    // 还原默认
    void restoreDefault();
    // 测量参数
    QVariantMap testParam();
    // 计算通讯等待时间
    int calcCommWaitTime(double &value);
    // 检查积分时间溢出
    int checkIntegralTime(double value);
    // 检查帧溢出
    int checkFrameOverflow(int size);
    // 检查采样溢出
    int checkSampleOverflow(double value);
    // 扣暗底
    QVector<double> dealBotton(QVector<double> value);
    // 平滑数据
    QVector<double> smoothCurve(QVector<double> value);
    // 计算并插值光谱能量，value是波长和采样值与标准曲线比值的集合
    QPolygonF interpEnergy(QPolygonF value, double offset);

protected:
    HSpecSetting(HSpecSettingPrivate &p);

protected:
    double calcEnergy(double wave, double offset);
};

HE_DATA_END_NAMESPACE

#endif // HSPECSETTING_H
