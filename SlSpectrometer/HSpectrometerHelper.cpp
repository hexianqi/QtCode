#include "HSpectrometerHelper.h"
#include <math.h>

const double C1 = 3.741844e-12;     // cm
const double C2 = 1.438833;         // cm

vector<double> HSpectrometerHelper::xy2uv(double x, double y)
{
    auto u = 4 * x / (-2 * x + 12 * y + 3);
    auto v = 6 * y / (-2 * x + 12 * y + 3);
    return {u, v};
}

vector<double> HSpectrometerHelper::uv2xy(double u, double v)
{
    auto x = 3 * u / (4 + 2 * u - 8 * v);
    auto y = 2 * v / (4 + 2 * u - 8 * v);
    return {x, y};
}

vector<double> HSpectrometerHelper::uv2uvp(double u, double v)
{
    return {u, 1.5 * v};
}

vector<double> HSpectrometerHelper::uv2cd(double u, double v)
{
    auto c = (4 - u - 10 * v) / v;
    auto d = (1.708 * v + 0.404 - 1.481 * u) / v;
    return {c, d};
}

double HSpectrometerHelper::planck(double tc, double wave)
{
    wave *= 1e-7;
    return C1 / pow(wave, 5) / (exp(C2 / (wave * tc)) - 1);
}

double HSpectrometerHelper::planckPrime(double tc, double wave)
{
    wave *= 1e-7;
    auto temp = exp(C2 / wave / tc);
    return C1 * C2 * pow(tc, -2) * pow(wave, -6) * temp * pow(temp - 1, -2);
}

double HSpectrometerHelper::interpolate(double x, double x1, double y1, double x2, double y2)
{
    return (x - x1) * (y2 - y1) / (x2 - x1) + y1;
}

double HSpectrometerHelper::interpolate(double x, vector<double> xs, vector<double> ys)
{
    if (xs.size() != ys.size() || xs.size() < 2)
        return 0;

    unsigned int i;
    for (i = 1; i < xs.size() - 1; i++)
    {
        if (x <= xs[i])
            break;
    }
    return interpolate(x, xs[i - 1], ys[i - 1], xs[i], ys[i]);
}

vector<vector<double> > HSpectrometerHelper::interpolate(vector<double> xs, vector<double> ys, double x1, double x2, double interval)
{
    unsigned int i, j, n;
    double x, y;
    vector<double> xr, yr;

    if (xs.size() != ys.size() || xs.size() < 2)
        return {xr, yr};

    if (x2 < x1)
        swap(x1, x2);

    n = ceil((x2 - x1) / interval + 1);
    for (i = 0, j = 1; i < n; i++)
    {
        x = x1 + i * interval;
        for (; x > xs[j] && j < xs.size() - 1; j++);
        y = interpolate(x, xs[j-1], ys[j-1], xs[j], ys[j]);
        xr.push_back(x);
        yr.push_back(y);
    }
    return {xr, yr};
}

double HSpectrometerHelper::sum(vector<double> value)
{
    if (value.size() < 1)
        return 0.0;
    auto r = 0.0;
    for (auto v : value)
        r += v;
    return r;
}

double HSpectrometerHelper::mean(vector<double> value)
{
    if (value.size() < 1)
        return 0.0;
    return sum(value) / value.size();
}

vector<double> HSpectrometerHelper::percent(vector<double> value)
{
    if (value.size() < 1)
        return {};

    vector<double> result;
    auto max = value.front();
    for (auto v : value)
        if (v > max)
            max = v;
    for (auto v : value)
        result.push_back(100 * v / max);
    return result;
}
