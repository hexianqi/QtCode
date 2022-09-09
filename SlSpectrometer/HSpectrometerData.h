#pragma once

#include <vector>

using namespace std;

struct HSpectrometerData
{
    vector<double> Wave;
    vector<double> Energy;
    vector<double> EnergyPercent;
    // 能量参数
    double EnergyTotal;
    double EnergyMax;
    double WavePeak;
    double Bandwidth;
    // 色度参数
    double CoordinateX;
    double CoordinateY;
    double CoordinateU;
    double CoordinateV;
    double CoordinateUp;
    double CoordinateVp;
    double CoordinateC;
    double CoordinateD;
    double WaveDominant;
    double ColorTemperature;
    double ColorPurity;
    double Duv;
    // 显色指数
    vector<double> RenderingIndex;
    double RenderingIndexAvg;
    // 明视觉参数
    double VisionFlux;
    double VisionEfficien;
    double RatioRed;
    double RatioGreen;
    double RatioBlue;
};
