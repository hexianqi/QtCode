#ifndef HMATH_H
#define HMATH_H

#include "HeAlgorithm_global.h"

class QPointF;
class QPolygonF;

namespace He {
namespace Algorithm {
namespace Math {    // 数值算法

// 插值
HEALGORITHM_EXPORT double interpolate(double x, double x1, double y1, double x2, double y2);                             //2����ֵ
HEALGORITHM_EXPORT double interpolate(double x, QPointF p1, QPointF p2);
HEALGORITHM_EXPORT double interpolate(double x, QPolygonF poly);
HEALGORITHM_EXPORT QPolygonF interpolate(QPolygonF poly, double x1, double x2, double interval = 0.1);
HEALGORITHM_EXPORT QPolygonF interpolate(QPolygonF poly, double x1, double x2, double defaultValue, double interval);
HEALGORITHM_EXPORT double interpolateY(double y, QPointF p1, QPointF p2);                                          //2�㷴��ֵ
HEALGORITHM_EXPORT double interpolateY(double y, QPolygonF poly);
// 多项式拟合
HEALGORITHM_EXPORT bool polyfit(QVector<QPointF> points, QVector<double> &factors);

} // namespace Math
} // namespace Algorithm
} // namespace He

#endif // HMATH_H
