#ifndef HTESTGSL_H
#define HTESTGSL_H

#include <QtGui/QPolygonF>

class QWidget;

class HTestGsl
{
public:
    void polyEval();
    void polySolve();
    QList<QPolygonF> interpEval();
    QList<QPolygonF> linearFit();
    QList<QPolygonF> multiFit();
    QList<QPolygonF> multiFit2();
};

#endif // HTESTGSL_H
