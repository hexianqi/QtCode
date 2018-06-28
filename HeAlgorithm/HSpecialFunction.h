/***************************************************************************************************
**      2018-06-20  HSpecialFunction GSL特殊函数类。
**                  http://www.gnu.org/software/gsl/doc/html/specfunc.html
***************************************************************************************************/

#ifndef HSPECIALFUNCTION_H
#define HSPECIALFUNCTION_H

#include "HAlgorithmGlobal.h"

HE_ALGORITHM_BEGIN_NAMESPACE

class HE_ALGORITHM_EXPORT HSpecialFunction
{
public:
    // 埃里函数
    double airyAi(double x);
    double airyBi(double x);

public:
    // 规则的0阶圆柱贝塞尔函数值
    double besselJ0(double x);
    // 规则的1阶圆柱贝塞尔函数值
    double besselJ1(double x);
    // 规则的n阶圆柱贝塞尔函数值
    double besselJn(int n, double x);
    // 规则的[nmin, nmax]阶圆柱贝塞尔函数值
    QVector<double> besselJn(int nmin, int nmax, double x);
};

HE_ALGORITHM_END_NAMESPACE

#endif // HSPECIALFUNCTION_H
