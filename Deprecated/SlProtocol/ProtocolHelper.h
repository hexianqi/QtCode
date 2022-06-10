#pragma once

#include <vector>

using namespace std;

class CProtocolHelper
{
public:
    static double interpolate(double x1, double y1, double x2, double y2, double x);
    static double interpolate(vector<double> xa, vector<double> ya, double x);
    static vector<double> interpolate(vector<double> xa, vector<double> ya, double x1, double x2, double interval = 0.1);

public:
    static double planck(double wave, double tc);
};
