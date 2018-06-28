/***************************************************************************************************
**      2018-06-20  HGslHelper GSL帮助类。
***************************************************************************************************/

#ifndef HGSLHELPER_H
#define HGSLHELPER_H

#include "HAlgorithmGlobal.h"
#include <QPolygonF>

HE_ALGORITHM_BEGIN_NAMESPACE

class HGslHelper
{
public:
    static QPolygonF join(QVector<double> x, QVector<double> y);
    static void split(QPolygonF poly, QVector<double> &x, QVector<double> &y);
};

HE_ALGORITHM_END_NAMESPACE

#endif // HGSLHELPER_H
