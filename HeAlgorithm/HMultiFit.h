/***************************************************************************************************
**      2018-06-20  HMultiFit GSL最小二乘拟合函数类。
**                  http://www.gnu.org/software/gsl/doc/html/lls.html
***************************************************************************************************/

#ifndef HMULTIFIT_H
#define HMULTIFIT_H

#include "HAlgorithmGlobal.h"
#include <QPolygonF>

HE_ALGORITHM_BEGIN_NAMESPACE

class HE_ALGORITHM_EXPORT HMultiFit
{
public:
    HMultiFit();

public:
    static void linear(QPolygonF basis, QVector<double> w, QVector<double> &c, QVector<double> &cov, double *chisq);
};

HE_ALGORITHM_END_NAMESPACE

#endif // HMULTIFIT_H
