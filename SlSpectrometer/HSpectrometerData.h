#pragma once

#include <vector>

using namespace std;

struct HSpectrometerData
{
    vector<double> Wave;
    vector<double> TestEnergy;
    vector<double> TestEnergyPercent;
    vector<double> ReferenceEnergy;
    vector<double> ReferenceEnergyPercent;
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
    vector<double> RenderingIndex;  // 15
    double RenderingIndexAvg;
    // TM30
    double TM30_Rf;
    double TM30_Rg;
    vector<double> TM30_Rfi;    // 99
    vector<double> TM30_hj_at;  // 16
    vector<double> TM30_hj_bt;
    vector<double> TM30_hj_ar;
    vector<double> TM30_hj_br;
    vector<double> TM30_hj_atn;
    vector<double> TM30_hj_btn;
    vector<double> TM30_hj_arn;
    vector<double> TM30_hj_brn;
    vector<double> TM30_hj_Rf;
    vector<double> TM30_hj_Rcs;
    vector<double> TM30_hj_Rhs;
    // 明视觉参数
    double VisionFlux;
    double VisionEfficien;
    double RatioRed;
    double RatioGreen;
    double RatioBlue;
};
