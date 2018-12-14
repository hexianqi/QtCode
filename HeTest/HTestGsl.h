#ifndef HTESTGSL_H
#define HTESTGSL_H

#include "HeExample/HExampleGlobal.h"
#include <QPolygonF>

class QWidget;

class HTestGsl
{
public:
    void polyEval();
    void polySolve();

    QWidget *interpEval();
//    QWidget *linearFit();
//    QWidget *multiFit();
//    QWidget *multiFit2();
};

#endif // HTESTGSL_H
