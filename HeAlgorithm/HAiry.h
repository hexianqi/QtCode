/***************************************************************************************************
**      2018-12-06  HAiry 艾里函数类。
**                  http://www.gnu.org/software/gsl/doc/html/specfunc.html
***************************************************************************************************/

#pragma once

#include "HNamespace.h"

HE_BEGIN_NAMESPACE

class HAiry
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
    static double zero_Ai(unsigned int s);
    static double zero_Bi(unsigned int s);
    static double zero_Ai_deriv(unsigned int s);
    static double zero_Bi_deriv(unsigned int s);
};

HE_END_NAMESPACE
