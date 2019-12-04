/***************************************************************************************************
**      2018-12-06  HAiry 艾里函数类。
**                  http://www.gnu.org/software/gsl/doc/html/specfunc.html
***************************************************************************************************/

#ifndef HAIRY_H
#define HAIRY_H

#include "HAlgorithmGlobal.h"

HE_ALGORITHM_BEGIN_NAMESPACE

class HE_ALGORITHM_EXPORT HAiry
{
public:
    static double Ai(double x);
    static double Bi(double x);
    static double Ai_scaled(double x);
    static double Bi_scaled(double x);

public:
    static double Ai_deriv(double x);
    static double Bi_deriv(double x);
    static double Ai_deriv_scaled(double x);
    static double Bi_deriv_Scaled(double x);

public:
    static double zero_Ai(uint s);
    static double zero_Bi(uint s);
    static double zero_Ai_deriv(uint s);
    static double zero_Bi_deriv(uint s);
};

HE_ALGORITHM_END_NAMESPACE

#endif // HAIRY_H
