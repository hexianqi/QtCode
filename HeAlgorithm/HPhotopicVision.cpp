#include "HPhotopicVision.h"
#include "HInterp.h"
#include "HSpecData.h"
#include <QtCore/QFile>
#include <QtCore/QTextStream>

HE_ALGORITHM_BEGIN_NAMESPACE

HPhotopicVision::HPhotopicVision()
{
    readStandard();
}

void HPhotopicVision::calcSpectrum(HSpecData *data)
{
    if (data->Energy.isEmpty())
        return;

    int i,j;
    double r,g,b,t;
    double sum1,sum2;

    i = 0;
    j = 0;
    r = 0;
    g = 0;
    b = 0;
    sum1 = 0.0;
    sum2 = 0.0;
    while (i < data->Energy.size() && j < _stdData.size())
    {
        if (qAbs(data->Energy[i].x() - _stdData[j].x()) < 1e-6)
        {
            t = data->Energy[i].y() * _stdData[j].y();
            sum1 += data->Energy[i].y();
            sum2 += t;
            if (data->Energy[i].x() >= 380 && data->Energy[i].x() < 500)
                b += t;
            if (data->Energy[i].x() >= 500 && data->Energy[i].x() < 600)
                g += t;
            if (data->Energy[i].x() >= 600 && data->Energy[i].x() < 780)
                r += t;
            i++;
            j++;
        }
        else if (data->Energy[i].x() < _stdData[j].x())
            i++;
        else
            j++;
    }
    if (qFuzzyIsNull(sum2))
    {
        data->VisionEnergy = 0;
        data->VisionEnergyRatio = 0;
        data->RedRatio = 0;
        data->GreenRatio = 0;
        data->BlueRatio = 0;
    }
    else
    {
        auto rgb = r + g + b;
        data->VisionEnergy = sum2;
        data->VisionEnergyRatio = 1000 * sum1 / sum2 / 683;
        data->RedRatio = 100 * r / rgb;
        data->GreenRatio = 100 * g / rgb;
        data->BlueRatio = 100 * b / rgb;
    }
}

void HPhotopicVision::readStandard()
{
    int i,n;
    double x,y;
    QString str;
    QPolygonF poly;

    QFile file(":/dat/PhotopicVision.dat");
    file.open(QIODevice::ReadOnly);
    QTextStream in(&file);

    in >> str >> n;
    in >> str >> str;
    for (i = 0; i < n; i++)
    {
        in >> x >> y;
        poly.append(QPointF(x, y));
    }
    file.close();

    _stdData = HInterp::eval(poly, poly.first().x(), poly.last().x(), 0.1, HInterp::Cspline);
}

HE_ALGORITHM_END_NAMESPACE
