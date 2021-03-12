#pragma once

#include <QtGui/QPolygonF>

class HTestGsl
{
public:
    static void polyEval();
    static void polySolve();
    static QList<QPolygonF> interpEval();
    static QList<QPolygonF> linearFit();
    static QList<QPolygonF> multiFit();
    static QList<QPolygonF> multiFit2();
};
