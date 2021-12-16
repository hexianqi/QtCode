/***************************************************************************************************
**      2018-06-20  HInterp2D GSL二维插值函数类。
**                  http://www.gnu.org/software/gsl/doc/html/interp.html
***************************************************************************************************/

#pragma once

#include "HNamespace.h"
#include <QtCore/QVector>

HE_BEGIN_NAMESPACE

class HInterp2D
{
public:
    enum Interp2DType
    {
        Bilinear,           // 双线性插值
        Bicubic             // 双立方插值
    };

public:
    // 求值
    static double eval(QVector<double> xa, QVector<double> ya, QVector<double> za, double x, double y, Interp2DType type = Bilinear);
    // 求x一阶导数值
    static double eval_deriv_x(QVector<double> xa, QVector<double> ya, QVector<double> za, double x, double y, Interp2DType type = Bilinear);
    // 求y一阶导数值
    static double eval_deriv_y(QVector<double> xa, QVector<double> ya, QVector<double> za, double x, double y, Interp2DType type = Bilinear);
    // 求x二阶导数值
    static double eval_deriv_xx(QVector<double> xa, QVector<double> ya, QVector<double> za, double x, double y, Interp2DType type = Bilinear);
    // 求y二阶导数值
    static double eval_deriv_yy(QVector<double> xa, QVector<double> ya, QVector<double> za, double x, double y, Interp2DType type = Bilinear);
    // 求xy阶导数值
    static double eval_deriv_xy(QVector<double> xa, QVector<double> ya, QVector<double> za, double x, double y, Interp2DType type = Bilinear);
};

HE_END_NAMESPACE
