#ifndef HPHOTOPICVISION_H
#define HPHOTOPICVISION_H

#include <QPolygonF>

namespace He {
namespace Algorithm {
namespace Spectrum {

// 明视觉比例系数计算类
class HPhotopicVision
{
public:
    HPhotopicVision();

public:
    // 计算明视觉光谱能量比、红色比、蓝色比、绿色比
    void calcVisionRatio(QPolygonF value, double &energy, double &red, double &green, double &blue);
    // 计算明视觉光谱能量
    double calcVisionEnergy(QPolygonF value);

protected:
    void readStandard();

protected:
    QPolygonF _stdData;
};

} // namespace Spectrum
} // namespace Algorithm
} // namespace He

#endif // HPHOTOPICVISION_H
