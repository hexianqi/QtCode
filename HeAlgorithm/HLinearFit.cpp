#include "HLinearFit.h"
#include "HGslHelper.h"
#include "gsl/gsl_fit.h"

HE_ALGORITHM_BEGIN_NAMESPACE

QVector<double> HLinearFit::linear(QPolygonF basis)
{
    double sumsq;
    QVector<double> c, cov;
    linear(basis, c, cov, &sumsq);
    return c;
}

QVector<double> HLinearFit::linear(QPolygonF basis, QVector<double> w)
{
    double chisq;
    QVector<double> c, cov;
    linear(basis, w, c, cov, &chisq);
    return c;
}

void HLinearFit::linear(QPolygonF basis, QVector<double> &c, QVector<double> &cov, double *sumsq)
{
    double c0, c1, cov00, cov01, cov11;
    QVector<double> xa, ya;

    HGslHelper::split(basis, xa, ya);
    gsl_fit_linear(xa.data(), 1, ya.data(), 1, basis.size(), &c0, &c1, &cov00, &cov01, &cov11, sumsq);
    c = QVector<double>() << c0 << c1;
    cov = QVector<double>() << cov00 << cov01 << cov11;
}

void HLinearFit::linear(QPolygonF basis, QVector<double> w, QVector<double> &c, QVector<double> &cov, double *chisq)
{
    double c0, c1, cov00, cov01, cov11;
    QVector<double> xa, ya;

    HGslHelper::split(basis, xa, ya);
    gsl_fit_wlinear(xa.data(), 1, w.data(), 1, ya.data(), 1, basis.size(), &c0, &c1, &cov00, &cov01, &cov11, chisq);
    c = QVector<double>() << c0 << c1;
    cov = QVector<double>() << cov00 << cov01 << cov11;
}

void HLinearFit::linearEst(double x, QVector<double> c, QVector<double> cov, double *y, double *y_err)
{
    Q_ASSERT(c.size() >= 2 && cov.size() >= 3);
    gsl_fit_linear_est(x, c[0], c[1], cov[0], cov[1], cov[2], y, y_err);
}

double HLinearFit::mul(QPolygonF basis)
{
    double c, cov, sumsq;
    mul(basis, &c, &cov, &sumsq);
    return c;
}

double HLinearFit::mul(QPolygonF basis, QVector<double> w)
{
    double c, cov, chisq;
    mul(basis, w, &c, &cov, &chisq);
    return c;
}

void HLinearFit::mul(QPolygonF basis, double *c, double *cov, double *sumsq)
{
    QVector<double> xa, ya;
    HGslHelper::split(basis, xa, ya);
    gsl_fit_mul(xa.data(), 1, ya.data(), 1, basis.size(), c, cov, sumsq);
}

void HLinearFit::mul(QPolygonF basis, QVector<double> w, double *c, double *cov, double *chisq)
{
    QVector<double> xa, ya;
    HGslHelper::split(basis, xa, ya);
    gsl_fit_wmul(xa.data(), 1, w.data(), 1, ya.data(), 1, basis.size(), c, cov, chisq);
}

void HLinearFit::mulEst(double x, double c, double cov, double *y, double *y_err)
{
    gsl_fit_mul_est(x, c, cov, y, y_err);
}

HE_ALGORITHM_END_NAMESPACE
