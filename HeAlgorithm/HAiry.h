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
    double Ai(double x);
    double Bi(double x);
    double Ai_scaled(double x);
    double Bi_scaled(double x);

public:
    double Ai_deriv(double x);
    double Bi_deriv(double x);
    double Ai_deriv_scaled(double x);
    double Bi_deriv_Scaled(double x);

public:
    double zero_Ai(uint s);
    double zero_Bi(uint s);
    double zero_Ai_deriv(uint s);
    double zero_Bi_deriv(uint s);
};

HE_ALGORITHM_END_NAMESPACE

#endif // HAIRY_H
