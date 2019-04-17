#ifndef HTESTGSL_H
#define HTESTGSL_H

#include "HeExample/HExampleGlobal.h"
#include <QtGui/QPolygonF>

class QWidget;

class HTestGsl
{
public:
    void polyEval();
    void polySolve();
    QList<QPolygonF> interpEval();
//    QWidget *linearFit();
//    QWidget *multiFit();
//    QWidget *multiFit2();
};

#endif // HTESTGSL_H
