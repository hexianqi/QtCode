#ifndef HTESTGSL_H
#define HTESTGSL_H

#include "HeExample/HExampleGlobal.h"
#include <QPolygonF>

HE_EXAMPLE_BEGIN_NAMESPACE
class HPolynomials;
class HSpecial;
class HInterpolation;
HE_EXAMPLE_END_NAMESPACE
HE_EXAMPLE_USE_NAMESPACE

class HTestGsl
{
public:
    HTestGsl();
    ~HTestGsl();

public:
    void polyEval();
    void polySolve();
    QPolygonF specialAirAi();
    QPolygonF specialAirBi();
    QPolygonF interpolation(QPolygonF basis);

private:
    HPolynomials *_polynomials;
    HSpecial *_special;
    HInterpolation *_interpolation;
};

#endif // HTESTGSL_H
