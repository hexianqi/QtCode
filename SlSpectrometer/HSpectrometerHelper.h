#pragma once

#include <vector>

using namespace std;

class HSpectrometerHelper
{
public:
    static vector<double> xy2uv(double x, double y);
    static vector<double> uv2xy(double u, double v);
    static vector<double> uv2uvp(double u, double v);
    static vector<double> uv2cd(double u, double v);
    static double planck(double tc, double wave);
    static double planckPrime(double tc, double wave);
    static double interpolate(double x, double x1, double y1, double x2, double y2);
    static double interpolate(double x, vector<double> xs, vector<double> ys);
    static vector<vector<double> > interpolate(vector<double> xs, vector<double> ys, double x1, double x2, double interval = 0.1);

};

