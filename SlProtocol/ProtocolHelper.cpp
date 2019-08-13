#include "ProtocolHelper.h"
#include <math.h>

double CProtocolHelper::interpolate(double x1, double y1, double x2, double y2, double x)
{
    return (x - x1) * (y2 - y1) / (x2 - x1) + y1;
}

double CProtocolHelper::interpolate(vector<double> xa, vector<double> ya, double x)
{
    if (xa.size() != ya.size() || xa.size() < 2)
        return 0;

    size_t i;
    for (i = 1; i < xa.size() - 1; i++)
    {
        if (x <= xa[i])
            break;
    }
    return interpolate(xa[i - 1], ya[i - 1], xa[i], ya[i], x);
}

vector<double> CProtocolHelper::interpolate(vector<double> xa, vector<double> ya, double x1, double x2, double interval)
{
    int i, j, n;
    double t;
    vector<double> r;
    if (xa.size() != ya.size() || xa.size() < 2)
        return r;

    if (x2 < x1)
    {
        t = x2;
        x2 = x1;
        x1 = t;
    }

    n = ceill((x2 - x1) / interval + 1);
    for (i = 0, j = 1; i < n; i++)
    {
        t = x1 + i * interval;
        for (; t > xa[j] && j < xa.size() - 1; j++);
        r.push_back(interpolate(xa[j - 1], ya[j - 1], xa[j], ya[j], t));
    }
    return r;
}

/***************************************************************************************************
**      普朗克常量C1和C2计算公式，单位W*m和K*m
**      h = 6.6260693e-34;
**      c = 299792458;
**      k = 1.3806505e-23;
**      C1 = 2 * M_PI * h * c * c;
**      C2 = h * c / k;
***************************************************************************************************/
double CProtocolHelper::planck(double wave, double tc)
{
    const double C1 = 3.741844e-12;
    const double C2 = 1.438833;
    wave *= 1e-7;
    return C1 / pow(wave, 5) / (exp(C2 / (wave * tc)) - 1);
}
