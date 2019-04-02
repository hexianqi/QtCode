#include "HTestGsl.h"
#include "HeAlgorithm/HInterp.h"
#include "HeAlgorithm/HPolynomial.h"
#include "HeAlgorithm/HLinearFit.h"
#include "HeAlgorithm/HMultiFit.h"
#include <QFile>
#include <QTextStream>
#include <QtMath>
#include <QRandomGenerator>
#include <QDebug>

HE_ALGORITHM_USE_NAMESPACE

QPolygonF readCieDay()
{
    int i,n;
    QString str;

    QFile file(":/dat/CIE_DAY.dat");
    file.open(QIODevice::ReadOnly);
    QTextStream in(&file);

    QPolygonF poly;
    double x,y,t1,t2;

    in >> str >> n;
    str = in.readLine();
    str = in.readLine();

    for (i = 0; i < n; i++)
    {
        in >> x >> y >> t1 >> t2;
        poly << QPointF(x,y);
    }
    file.close();
    return poly;
}

// polynomial: P(x) =  1 + 0.5 * x + 0.3 * x^2
void HTestGsl::polyEval()
{
    QVector<double> a;
    a << 1.0 << 0.5 << 0.3;
    auto x = 0.5;
    auto y = HPolynomial::eval(a, x);
    qDebug() << __FUNCTION__;
    qDebug() << "P(x) =  1 + 0.5 * x + 0.3 * x^2";
    qDebug() << "P(0.5) = " << y;
}

// polynomial: P(x) =  -1 + x^5
void HTestGsl::polySolve()
{
    QVector<double> a;
    a << -1 << 0 << 0 << 0 << 0 << 1;
    auto r = HPolynomial::complex_solve(a);
    qDebug() << __FUNCTION__;
    qDebug() << "P(x) =  -1 + x^5";
    for (int i = 0; i < r.size(); i++)
        qDebug() << QString("z%1 = %2 + %3 * i").arg(i).arg(GSL_REAL(r[i])).arg(GSL_IMAG(r[i]));
}

QList<QPolygonF> HTestGsl::interpEval()
{
    auto p1 = readCieDay();
    auto p2 = HInterp::eval(p1, p1.first().x() - 10, p1.last().x() + 10, 0.1, HInterpType::Cspline);
    return QList<QPolygonF>() << p1 << p2;
}

//QWidget *HTestGsl::linearFit()
//{
//    QPolygonF p1;
//    QList<QPolygonF> list;

//    p1 << QPointF(1970, 12) << QPointF(1980, 11) << QPointF(1990, 14) << QPointF(2000, 13);
//    list << p1;
//    for (int j = 0; j < 4; j++)
//    {
//        double chisq, xf, yf, yf_err;
//        QPolygonF p2, p3, p4;
//        QVector<double> c, cov, w;

//        w.fill(1, 4);
//        w[j] = 10;
//        HLinearFit::linear(p1, w, c, cov, &chisq);

//        for (int i = -30; i < 130; i++)
//        {
//            xf = p1.first().x() + (p1.last().x() - p1.first().x()) * i / 100.0;
//            HLinearFit::linearEst(xf, c, cov, &yf, &yf_err);
//            p2 << QPointF(xf, yf);
//            p3 << QPointF(xf, yf + yf_err);
//            p4 << QPointF(xf, yf - yf_err);
//        }
//        list << p2 << p3 << p4;

//        qDebug() << __FUNCTION__;
//        qDebug() << QString("best fit: Y = %1 + %2 * x").arg(c[0]).arg(c[1]);
//        qDebug() << QString("chisq = %1").arg(chisq);
//        qDebug() << QString("covariance matrix:");
//        qDebug() << QString("[ %1, %2").arg(cov[0]).arg(cov[1]);
//        qDebug() << QString("  %1, %2 ]").arg(cov[1]).arg(cov[2]);
//    }
//    return HTestChart::lineChart(list);
//}

//QWidget *HTestGsl::multiFit()
//{
//    int i, j;
//    double chisq;
//    QString text;
//    QPolygonF p1, p2, p3, p4;
//    QVector<double> w,c,cov;

//    c.resize(5);
//    for (double x = 0.1; x < 2; x+= 0.1)
//    {
//        auto y = qExp(x);
//        auto sigma = 0.1 * y;
//        auto dy = ((qrand() % 10) - 5) / 50.0;
//        p1 << QPointF(x, y * (1 + dy));
//        w << sigma;
//    }
//    HMultiFit::linear(p1, w, c, cov, &chisq);

//    for (double xf = 0.05; xf < 2.05; xf += 0.01)
//    {
//        double yf, yf_err;
//        HMultiFit::linearEst(xf, c, cov, &yf, &yf_err);
//        p2 << QPointF(xf, yf);
//        p3 << QPointF(xf, yf + yf_err);
//        p4 << QPointF(xf, yf - yf_err);
//    }

//    qDebug() << __FUNCTION__;
//    text = QString("best fit: Y = %1").arg(c[0]);
//    for (i = 1; i < c.size(); i++)
//        text += QString(" + %1 * x^%2").arg(c[i]).arg(i);
//    qDebug() << text;
//    qDebug() << QString("chisq = %1").arg(chisq);
//    qDebug() << QString("covariance matrix:");
//    for (i = 0; i < c.size(); i++)
//    {
//        QStringList list;
//        for (j = 0; j < c.size(); j++)
//            list << QString(" %1").arg(cov[i * c.size() + j]);
//        qDebug() << list.join(",");
//    }

//    return HTestChart::lineChart(QList<QPolygonF>() << p1 << p2 << p3 << p4);
//}

//QWidget *HTestGsl::multiFit2()
//{
//    int i, j;

//    QPolygonF p1;
//    QVector<double> c,cov;
//    QList<HRobustType> types;
//    QList<QPolygonF> list;

//    types << HRobustType::Bisquare << HRobustType::Cauchy << HRobustType::Fair
//          << HRobustType::Huber << HRobustType::Ols << HRobustType::Welsch;
//    c.resize(5);
//    for (double x = 0.1; x < 2; x+= 0.1)
//    {
//        auto y = qExp(x);
//        auto dy = ((qrand() % 10) - 5) / 50.0;
//        p1 << QPointF(x, y * (1 + dy));
//    }
//    list << p1;

//    for(auto type : types)
//    {
//        QString text;
//        QPolygonF p2, p3, p4;

//        HMultiFit::robust(p1, c, cov, type);
//        for (double xf = 0.05; xf < 2.05; xf += 0.01)
//        {
//            double yf, yf_err;
//            HMultiFit::robustEst(xf, c, cov, &yf, &yf_err);
//            p2 << QPointF(xf, yf);
//            p3 << QPointF(xf, yf + yf_err);
//            p4 << QPointF(xf, yf - yf_err);
//        }

//        qDebug() << __FUNCTION__;
//        text = QString("best fit: Y = %1").arg(c[0]);
//        for (i = 1; i < c.size(); i++)
//            text += QString(" + %1 * x^%2").arg(c[i]).arg(i);
//        qDebug() << text;
//        qDebug() << QString("covariance matrix:");
//        for (i = 0; i < c.size(); i++)
//        {
//            QStringList list;
//            for (j = 0; j < c.size(); j++)
//                list << QString(" %1").arg(cov[i * c.size() + j]);
//            qDebug() << list.join(",");
//        }
//        list << p2 << p3 << p4;
//    }

//    return HTestChart::lineChart(list);
//}
