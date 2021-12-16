/***************************************************************************************************
**      2021-11-16  HMatrix 矩阵
**                  http://www.gnu.org/software/gsl/doc/html/vectors.html
**                  http://www.gnu.org/software/gsl/doc/html/blas.html
***************************************************************************************************/

#pragma once

#include "HNamespace.h"
#include "gsl/gsl_matrix.h"
#include <QtCore/QVector>

HE_BEGIN_NAMESPACE

class HMatrix
{
public:
    // c = a * b
    static void mul(gsl_matrix *a, gsl_matrix *b, gsl_matrix *c);
    static QVector<double> mul(gsl_matrix *a, QVector<double> b);
    // 求逆
    static void inverse(gsl_matrix *a);
};

HE_END_NAMESPACE

