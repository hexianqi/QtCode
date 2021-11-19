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
    while (i < data->Energy.size() && j < _standard.size())
    {
        if (qAbs(data->Energy[i].x() - _standard[j].x()) < 1e-6)
        {
            t = data->Energy[i].y() * _standard[j].y();
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
        else if (data->Energy[i].x() < _standard[j].x())
            i++;
        else
            j++;
    }
    if (qFuzzyIsNull(sum1))
    {
        data->VisionFlux = 0;
        data->VisionEfficien = 0;
        data->RatioRed = 0;
        data->RatioGreen = 0;
        data->RatioBlue = 0;
    }
    else
    {
        auto rgb = r + g + b;
        data->VisionFlux = 683 * sum2;              // lm
        data->VisionEfficien = 683 * sum2 / sum1;   // lm/W
        data->RatioRed = 100 * r / rgb;
        data->RatioGreen = 100 * g / rgb;
        data->RatioBlue = 100 * b / rgb;
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

    _standard = HInterp::eval(poly, poly.first().x(), poly.last().x(), 0.1, HInterp::Cspline);
}

HE_ALGORITHM_END_NAMESPACE
