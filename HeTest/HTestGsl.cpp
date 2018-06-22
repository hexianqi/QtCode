#include "HTestGsl.h"
#include "HeExample/HPolynomials.h"
#include "HeExample/HSpecial.h"
#include "HeExample/HInterpolation.h"
#include <QDebug>

HTestGsl::HTestGsl()
{
    _polynomials = new HPolynomials();
    _special = new HSpecial();
    _interpolation = new HInterpolation();
}

HTestGsl::~HTestGsl()
{
    delete _polynomials;
    delete _special;
    delete _interpolation;
}

void HTestGsl::polyEval()
{
    /* polynomial: P(x) =  1 + 0.5 * x + 0.3 * x^2  */

    QVector<double> a;
    a << 1.0 << 0.5 << 0.3;
    auto x = 0.5;
    auto y = _polynomials->eval(a, x);

    qDebug() << __FUNCTION__;
    qDebug() << "P(x) =  1 + 0.5 * x + 0.3 * x^2";
    qDebug() << "P(0.5) = " << y;
}

void HTestGsl::polySolve()
{
    /* polynomial: P(x) =  -1 + x^5 */

    QVector<double> a;
    a << -1 << 0 << 0 << 0 << 0 << 1;

    auto r = _polynomials->solve(a);

    qDebug() << __FUNCTION__;
    qDebug() << "P(x) =  -1 + x^5";
    for (int i = 0; i < r.size(); i++)
        qDebug() << QString("z%1 = %2 + %3 * i").arg(i).arg(r[i].x()).arg(r[i].y());

}

QPolygonF HTestGsl::specialAirAi()
{
    QPolygonF r;
    for (int i = -100; i <= 100; i++)
        r << QPointF(i, _special->airyAi(i));
    return r;
}

QPolygonF HTestGsl::specialAirBi()
{
    QPolygonF r;
    for (int i = -100; i < 0; i++)
        r << QPointF(i, _special->airyBi(i));
    return r;
}

QPolygonF HTestGsl::interpolation(QPolygonF basis)
{
    return _interpolation->splineEval(basis, basis.first().x() - 10, basis.last().x() + 10);
}
