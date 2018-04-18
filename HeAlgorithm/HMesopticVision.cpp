#include "HMesopticVision.h"
#include "HMath.h"
#include <QFile>
#include <QTextStream>

using namespace He::Algorithm::Spectrum;

HMesopticVision::HMesopticVision()
{
    initialize();
}

double HMesopticVision::calcRatio(QString type, double value)
{
    if (!_stdData.contains(type))
        return 0;
    return Math::interpolate(value, _stdData[type]);
}

void HMesopticVision::initialize()
{
    int i,j;
    double y;
    double x[12];
    QString str1,str2,type;
    QPolygonF poly;

    QFile file(":/dat/MesopticVision.dat");
    file.open(QIODevice::ReadOnly);
    QTextStream in(&file);

    in >> str1;
    in >> str1 >> str2;
    in >> str1 >> str2;
    for (i = 0; i < 12; i++)
        in >> x[i];
    for (i = 0; i < 19; i++)
    {
        in >> str1 >> str2;
        type = str1 + " " + str2;
        poly.clear();
        for (j = 0; j < 12; j++)
        {
            in >> y;
            poly.append(QPointF(x[j], y));
        }
        _stdData[type] = poly;
    }

    file.close();
}
