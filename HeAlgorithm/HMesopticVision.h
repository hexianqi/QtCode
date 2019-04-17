/***************************************************************************************************
**      2018-06-19  HMesopticVision 常用路灯不同亮度下的中间视觉照度与明视觉照度的比例系数计算类。
***************************************************************************************************/

#ifndef HMESOPTICVISION_H
#define HMESOPTICVISION_H

#include "HAlgorithmGlobal.h"
#include <QtCore/QHash>
#include <QtGui/QPolygonF>

HE_ALGORITHM_BEGIN_NAMESPACE

class HMesopticVision
{
public:
    HMesopticVision();

public:
    // 源类型
    QStringList sourceTypes() const;
    // 计算明视觉比例
    double calcRatio(QString type, double value);

protected:
    void readStandard();

protected:
    QHash<QString, QPolygonF> _stdData;
};

HE_ALGORITHM_END_NAMESPACE

#endif // HMESOPTICVISION_H
