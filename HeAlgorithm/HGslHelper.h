/***************************************************************************************************
**      2018-06-20  HGslHelper GSL帮助类。
***************************************************************************************************/

#ifndef HGSLHELPER_H
#define HGSLHELPER_H

#include "HAlgorithmGlobal.h"
#include "gsl/gsl_matrix.h"
#include <QtGui/QPolygonF>

HE_ALGORITHM_BEGIN_NAMESPACE

class HGslHelper
{
public:
    static QPolygonF join(QVector<double> xa, QVector<double> ya);
    static void split(QPolygonF poly, QVector<double> &xa, QVector<double> &ya);

public:
    static QPointF formGsl(gsl_complex z);
    static QPolygonF formGsl(QVector<gsl_complex> za);
    static QVector<double> fromGsl(gsl_vector *v);
    static QVector<double> fromGsl(gsl_matrix *m);
};

HE_ALGORITHM_END_NAMESPACE

#endif // HGSLHELPER_H
