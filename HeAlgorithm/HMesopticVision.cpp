#include "HMesopticVision.h"
#include "HInterp.h"
#include <QFile>
#include <QTextStream>

HE_ALGORITHM_BEGIN_NAMESPACE

HMesopticVision::HMesopticVision()
{
    readStandard();
}

QStringList HMesopticVision::sourceTypes() const
{
    return _stdData.keys();
}

double HMesopticVision::calcRatio(QString type, double value)
{
    if (!_stdData.contains(type))
        return 0;
    return HInterp::eval(_stdData[type], value, HInterpType::Cspline);
}

void HMesopticVision::readStandard()
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

HE_ALGORITHM_END_NAMESPACE
