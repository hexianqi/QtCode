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
    // z = x + y * i
    static QPointF toPointF(gsl_complex z);
    static QPolygonF toPolygonF(QVector<gsl_complex> z);
    // z = x + y * i
    static gsl_complex fromPoint(double x, double y);
    // z = r * exp^(i * θ) = r(cos(θ) + sin(θ) * i)
    static gsl_complex fromPolar(double r, double theta);

public:
    static QVector<double> toVector(gsl_vector *);
    static QVector<double> toVector(gsl_matrix *);
};

HE_ALGORITHM_END_NAMESPACE
