#include "HPhotopicVision.h"
#include "HMath.h"
#include <QFile>
#include <QTextStream>

HE_ALGORITHM_BEGIN_NAMESPACE

HPhotopicVision::HPhotopicVision()
{
    readStandard();
}

void HPhotopicVision::calcVisionRatio(QPolygonF value, double &energy, double &red, double &green, double &blue)
{
    int i,j;
    double r,g,b,t;
    double rgb,sum1,sum2;

    i = 0;
    j = 0;
    r = 0;
    g = 0;
    b = 0;
    sum1 = 0.0;
    sum2 = 0.0;
    while (i < value.size() && j < _stdData.size())
    {
        if (qAbs(value[i].x() - _stdData[j].x()) < 1e-6)
        {
            t = value[i].y() * _stdData[j].y();
            sum1 += value[i].y();
            sum2 += t;
            if (value[i].x() >= 380 && value[i].x() < 500)
                b += t;
            if (value[i].x() >= 500 && value[i].x() < 600)
                g += t;
            if (value[i].x() >= 600 && value[i].x() < 780)
                r += t;
            i++;
            j++;
        }
        else if (value[i].x() < _stdData[j].x())
            i++;
        else
            j++;
    }
    if (qFuzzyIsNull(sum2))
    {
        energy = 0;
        red = 0;
        green = 0;
        blue = 0;
    }
    else
    {
        rgb = r + g + b;
        energy = 1000 * sum1 / sum2 / 683;
        red = 100 * r / rgb;
        green = 100 * g / rgb;
        blue = 100 * b / rgb;
    }
}

double HPhotopicVision::calcVisionEnergy(QPolygonF value)
{
    int i = 0;
    int j = 0;
    double energy = 0;
    while (i < value.size() && j < _stdData.size())
    {
        if (qAbs(value[i].x() - _stdData[j].x()) < 1e-6)
        {
            energy += value[i].y() * _stdData[j].y();
            i++;
            j++;
        }
        else if (value[i].x() < _stdData[j].x())
            i++;
        else
            j++;
    }
    return energy;
}

void HPhotopicVision::readStandard()
{
    int i,n;
    double x,y;
    QString str;
    QVector<double> X,Y;
    QPolygonF poly;

    QFile file(":/dat/PhotopicVision.dat");
    file.open(QIODevice::ReadOnly);
    QTextStream in(&file);

    in >> str >> n;
    X.resize(n);
    Y.resize(n);
    in >> str >> str;
    for (i = 0; i < n; i++)
    {
        in >> x >> y;
        poly.append(QPointF(x, y));
    }
    file.close();

    _stdData = HMath::interpolate(poly, poly.first().x(), poly.last().x(), 0.1);
}

HE_ALGORITHM_END_NAMESPACE
