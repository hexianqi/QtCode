/***************************************************************************************************
**      2018-06-20  HGslHelper GSL帮助类。
***************************************************************************************************/

#pragma once

#include "HAlgorithmGlobal.h"
#include "gsl/gsl_matrix.h"
#include <QtGui/QPolygonF>

HE_ALGORITHM_BEGIN_NAMESPACE

class HGslHelper
{
public:
    static QPolygonF join(QVector<double> x, QVector<double> y);
    static void split(QPolygonF poly, QVector<double> &x, QVector<double> &y);

public:
    static QPointF formGsl(gsl_complex z);
    static QPolygonF formGsl(QVector<gsl_complex> z);
    static QVector<double> fromGsl(gsl_vector *v);
    static QVector<double> fromGsl(gsl_matrix *m);
};

HE_ALGORITHM_END_NAMESPACE
