#include "HLinearFit.h"
#include "HGslHelper.h"
#include "gsl/gsl_fit.h"

HE_ALGORITHM_BEGIN_NAMESPACE

QVector<double> HLinearFit::linear(QPolygonF basis)
{
    double sumsq;
    QVector<double> ca, cova;
    linear(basis, ca, cova, &sumsq);
    return ca;
}

QVector<double> HLinearFit::linear(QPolygonF basis, QVector<double> wa)
{
    double chisq;
    QVector<double> ca, cova;
    linear(basis, wa, ca, cova, &chisq);
    return ca;
}

void HLinearFit::linear(QPolygonF basis, QVector<double> &ca, QVector<double> &cova, double *sumsq)
{
    double c0, c1, cov00, cov01, cov11;
    QVector<double> xa, ya;

    HGslHelper::split(basis, xa, ya);
    gsl_fit_linear(xa.data(), 1, ya.data(), 1, basis.size(), &c0, &c1, &cov00, &cov01, &cov11, sumsq);
    ca = QVector<double>() << c0 << c1;
    cova = QVector<double>() << cov00 << cov01 << cov11;
}

void HLinearFit::linear(QPolygonF basis, QVector<double> wa, QVector<double> &ca, QVector<double> &cova, double *chisq)
{
    double c0, c1, cov00, cov01, cov11;
    QVector<double> xa, ya;

    HGslHelper::split(basis, xa, ya);
    gsl_fit_wlinear(xa.data(), 1, wa.data(), 1, ya.data(), 1, basis.size(), &c0, &c1, &cov00, &cov01, &cov11, chisq);
    ca = QVector<double>() << c0 << c1;
    cova = QVector<double>() << cov00 << cov01 << cov11;
}

void HLinearFit::linear_est(double x, QVector<double> ca, QVector<double> cova, double *y, double *y_err)
{
    Q_ASSERT(ca.size() >= 2 && cova.size() >= 3);
    gsl_fit_linear_est(x, ca[0], ca[1], cova[0], cova[1], cova[2], y, y_err);
}

double HLinearFit::mul(QPolygonF basis)
{
    double c, cov, sumsq;
    mul(basis, &c, &cov, &sumsq);
    return c;
}

double HLinearFit::mul(QPolygonF basis, QVector<double> wa)
{
    double c, cov, chisq;
    mul(basis, wa, &c, &cov, &chisq);
    return c;
}

void HLinearFit::mul(QPolygonF basis, double *c, double *cov, double *sumsq)
{
    QVector<double> xa, ya;
    HGslHelper::split(basis, xa, ya);
    gsl_fit_mul(xa.data(), 1, ya.data(), 1, basis.size(), c, cov, sumsq);
}

void HLinearFit::mul(QPolygonF basis, QVector<double> wa, double *c, double *cov, double *chisq)
{
    QVector<double> xa, ya;
    HGslHelper::split(basis, xa, ya);
    gsl_fit_wmul(xa.data(), 1, wa.data(), 1, ya.data(), 1, basis.size(), c, cov, chisq);
}

void HLinearFit::mul_est(double x, double c, double cov, double *y, double *y_err)
{
    gsl_fit_mul_est(x, c, cov, y, y_err);
}

HE_ALGORITHM_END_NAMESPACE
