#ifndef HMESOPTICVISION_H
#define HMESOPTICVISION_H

#include <QHash>
#include <QPolygonF>

namespace He {
namespace Algorithm {
namespace Spectrum {

// 常用路灯不同亮度下的中间视觉照度与明视觉照度的比例系数计算类
class HMesopticVision
{
public:
    HMesopticVision();

public:
    QStringList sourceTypes() const { return _stdData.keys(); }
    // 计算明视觉比例
    double calcRatio(QString type, double value);

protected:
    void initialize();

protected:
    QHash<QString, QPolygonF> _stdData;
};

} // namespace Spectrum
} // namespace Algorithm
} // namespace He

#endif // HMESOPTICVISION_H
