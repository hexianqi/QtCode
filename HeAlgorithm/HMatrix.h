/***************************************************************************************************
**      2021-11-16  HMatrix 矩阵
**                  http://www.gnu.org/software/gsl/doc/html/vectors.html
**                  http://www.gnu.org/software/gsl/doc/html/blas.html
***************************************************************************************************/

#pragma once

#include "HAlgorithmGlobal.h"
#include "gsl/gsl_matrix.h"

HE_ALGORITHM_BEGIN_NAMESPACE

class HE_ALGORITHM_EXPORT HMatrix
{
public:
    // c = a * b
    static void mul(gsl_matrix *a, gsl_matrix *b, gsl_matrix *c);
    //
    static QVector<double> mul(gsl_matrix *a, QVector<double> b);
    // 求逆
    static void inverse(gsl_matrix *a);
};

HE_ALGORITHM_END_NAMESPACE

