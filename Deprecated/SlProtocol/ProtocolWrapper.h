#pragma once

extern "C"
{
    __declspec(dllexport) bool OpenProtocol();
    __declspec(dllexport) bool CloseProtocol();
    __declspec(dllexport) bool SetIntegralTime(double value);
    __declspec(dllexport) bool SetSmooth(int times, int range);
    __declspec(dllexport) bool GetSpectrumSample(int value[], int *size, double *percent, bool fit);
    __declspec(dllexport) bool GetSpectrumEnergy(double value[], int *size, double *percent);
    __declspec(dllexport) double PelsToWave(int value);
    __declspec(dllexport) double HandleNonlinear(int value);
    __declspec(dllexport) bool SetStdCurve(double value[], int size);
}
