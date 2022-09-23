#pragma once

#include "HSpectrometerData.h"

extern "C"
{
    __declspec(dllexport) bool openSpectrometers(int index);
    __declspec(dllexport) bool closeSpectrometers(int index);
    __declspec(dllexport) bool setStdCurve(int index, double *value, int size);
    __declspec(dllexport) bool setIntegrationTime(int index, double value);
    __declspec(dllexport) bool getWave(int index, double *value, int size);
    __declspec(dllexport) double pelsToWave(int index, double value);
    __declspec(dllexport) bool getSample(int index, double *value, int size);
    __declspec(dllexport) bool getSampleI(int index, double integrationTime, double *value, int size);
    __declspec(dllexport) bool getSN(int index, unsigned char *value, int size);
    __declspec(dllexport) bool clearState(int index);
    __declspec(dllexport) bool queryState(int index, int *value);
    __declspec(dllexport) bool startSample(int index, double integrationTime);
    __declspec(dllexport) bool getSampleT(int index, double *value, int size);
    __declspec(dllexport) bool getSpectrometerData(int index, HSpectrometerData *data, double *sample, int size);
}
