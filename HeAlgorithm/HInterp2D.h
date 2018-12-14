/***************************************************************************************************
**      2018-06-20  HInterp2D GSL二维插值函数类。
**                  http://www.gnu.org/software/gsl/doc/html/interp.html
***************************************************************************************************/

#ifndef HINTERP2D_H
#define HINTERP2D_H

#include "HAlgorithmGlobal.h"
#include <QPolygonF>

HE_ALGORITHM_BEGIN_NAMESPACE

enum HInterp2DType
{
    Bilinear,           // 双线性插值
    Bicubic             // 双立方插值
};

class HE_ALGORITHM_EXPORT HInterp2D
{
public:
    // 求值
    static double eval(QVector<double> xa, QVector<double> ya, QVector<double> za, double x, double y, HInterp2DType type = HInterp2DType::Bilinear);
    // 求x一阶导数值
    static double eval_deriv_x(QVector<double> xa, QVector<double> ya, QVector<double> za, double x, double y, HInterp2DType type = HInterp2DType::Bilinear);
    // 求y一阶导数值
    static double eval_deriv_y(QVector<double> xa, QVector<double> ya, QVector<double> za, double x, double y, HInterp2DType type = HInterp2DType::Bilinear);
    // 求x二阶导数值
    static double eval_deriv_xx(QVector<double> xa, QVector<double> ya, QVector<double> za, double x, double y, HInterp2DType type = HInterp2DType::Bilinear);
    // 求y二阶导数值
    static double eval_deriv_yy(QVector<double> xa, QVector<double> ya, QVector<double> za, double x, double y, HInterp2DType type = HInterp2DType::Bilinear);
    // 求xy阶导数值
    static double eval_deriv_xy(QVector<double> xa, QVector<double> ya, QVector<double> za, double x, double y, HInterp2DType type = HInterp2DType::Bilinear);
};

HE_ALGORITHM_END_NAMESPACE

#endif // HINTERP2D_H
