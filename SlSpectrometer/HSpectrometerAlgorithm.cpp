#include "HSpectrometerAlgorithm.h"
#include "HSpectrometerHelper.h"
#include <math.h>

HSpectrometerAlgorithm::HSpectrometerAlgorithm()
{
    _cie1931 = new HCie1931();
    _cieUcs = new HCieUcs();
    _cieDaylight = new HCieDaylight();
    _photopicVision = new HPhotopicVision();
    _iesTm30 = new HIesTm30();
}

HSpectrometerAlgorithm::~HSpectrometerAlgorithm()
{
    delete _cie1931;
    delete _cieUcs;
    delete _cieDaylight;
    delete _photopicVision;
    delete _iesTm30;
}

HSpectrometerData *HSpectrometerAlgorithm::calcSpectrum(vector<double> wave, vector<double> energy)
{
    if (wave.empty() || wave.size() != energy.size())
        return nullptr;
    auto data = new HSpectrometerData;
    data->Wave = wave;
    data->TestEnergy = energy;
    calcEnergy(data);
    calcChromaticity(data);
    calcRenderingIndex(data);
    calcPhotopicVision(data);
    return data;
}

vector<double> HSpectrometerAlgorithm::wave()
{
    if (_wave.empty())
    {
        for (int i = 3800; i <= 7800; i++)
            _wave.push_back(i * 0.1);
    }
    return _wave;
}

void HSpectrometerAlgorithm::calcEnergy(HSpectrometerData *data)
{
    int i, n, size;
    double x, y, maxWave, maxEnergy, sumEnergy;

    size = data->Wave.size();
    n = 0;
    maxWave = 0;
    maxEnergy = 0;
    sumEnergy = 0;
    for (i = 0; i < size; i++)
    {
        x = data->Wave[i];
        y = data->TestEnergy[i];
        sumEnergy += y;
        if (y > maxEnergy)
        {
            n = i;
            maxWave = x;
            maxEnergy = y;
        }
    }

    x = 0;
    for (i = n - 1; i > 1; i--)
    {
        if (data->TestEnergy[i - 1] < maxEnergy / 2 && data->TestEnergy[i + 1] > maxEnergy / 2)
        {
            x = data->Wave[i];
            break;
        }
    }
    y = 0;
    for (i = n + 1; i < size - 1; i++)
    {
        if (data->TestEnergy[i - 1] > maxEnergy / 2 && data->TestEnergy[i + 1] < maxEnergy / 2)
        {
            y = data->Wave[i];
            break;
        }
    }
    data->EnergyTotal = sumEnergy;
    data->EnergyMax = maxEnergy;
    data->WavePeak = maxWave;
    data->Bandwidth = fabs(x - y);
    data->TestEnergyPercent = HSpectrometerHelper::percent(data->TestEnergy);
}

void HSpectrometerAlgorithm::calcChromaticity(HSpectrometerData *data)
{
    auto r1 = _cie1931->calcCoordinate(data->Wave, data->TestEnergy);
    data->CoordinateU = r1[0];
    data->CoordinateV = r1[1];
    data->CoordinateX = r1[2];
    data->CoordinateY = r1[3];
    data->CoordinateUp = r1[4];
    data->CoordinateVp = r1[5];
    data->CoordinateC = r1[6];
    data->CoordinateD = r1[7];
    auto r2 = _cie1931->calcWaveDominantPurity(data->CoordinateX, data->CoordinateY);
    data->WaveDominant = r2[0];
    data->ColorPurity = r2[1];
    auto r3 = _cieUcs->calcColorTemperatureDuv(data->CoordinateU, data->CoordinateV);
    data->ColorTemperature = r3[0];
    data->Duv = r3[1];
}

void HSpectrometerAlgorithm::calcRenderingIndex(HSpectrometerData *data)
{
    int i;
    double cki, dki;
    vector<double> Uri(15),Vri(15),Wri(15);
    vector<double> Uki(15),Vki(15),Wki(15),ukip(15),vkip(15);
    vector<double> E(15);
    vector<double> R(15);

    auto refer = _cieUcs->findCieUcs(data->ColorTemperature);
    if (refer.Tc < 2300)
        refer = calcCieUcs(data->ColorTemperature);
    auto ur = refer.ur;
    auto vr = refer.vr;
    auto cr = refer.cr;
    auto dr = refer.dr;
    for (i = 0; i < 15; i++)
    {
        Uri[i] = refer.Ur[i];
        Vri[i] = refer.Vr[i];
        Wri[i] = refer.Wr[i];
    }

    auto ck = data->CoordinateC;
    auto dk = data->CoordinateD;
    auto col = _cie1931->calcColorReflectance(data->Wave, data->TestEnergy);
    auto uki = col.at(0);
    auto vki = col.at(1);
    auto Yki = col.at(2);

    for (i = 0; i < 15; i++)
    {
        cki = (4 - uki[i] - 10 * vki[i]) / vki[i];
        dki = (1.708 * vki[i] + 0.404 - 1.481 * uki[i]) / vki[i];
        ukip[i] = (10.872 + 0.404 * cr * cki / ck - 4 * dr * dki / dk) / (16.518 + 1.481 * cr * cki / ck - dr * dki / dk);
        vkip[i] = 5.520 / (16.518 + 1.481 * cr * cki / ck - dr * dki / dk);
        Wki[i] = 25 * pow(Yki[i], 1.0/3) - 17;
        Uki[i] = 13 * Wki[i] * (ukip[i] - ur);
        Vki[i] = 13 * Wki[i] * (vkip[i] - vr);
        E[i] = sqrt(pow(Uri[i] - Uki[i], 2) + pow(Vri[i] - Vki[i], 2) + pow(Wri[i] - Wki[i], 2));
        R[i] = 100 - 4.6 * E[i];
    }

    auto ra = 0.0;
    for (i = 0; i < 8; i++)
        ra += R[i];
    data->RenderingIndex = R;
    data->RenderingIndexAvg = max(0.0, ra / 8.0);
}

void HSpectrometerAlgorithm::calcPhotopicVision(HSpectrometerData *data)
{
    auto r = _photopicVision->calcPhotopic(data->Wave, data->TestEnergy);
    data->VisionFlux = r[0];
    data->VisionEfficien = r[1];
    data->RatioRed = r[2];
    data->RatioGreen = r[3];
    data->RatioBlue = r[4];
}

void HSpectrometerAlgorithm::calcTM30(HSpectrometerData *data)
{
    data->ReferenceEnergy = _cieDaylight->calcRefSourceSpectrum(data->ColorTemperature, data->Wave);
    data->ReferenceEnergyPercent = HSpectrometerHelper::percent(data->ReferenceEnergy);
    auto r3 = _iesTm30->calc(data->Wave, data->TestEnergy, data->ReferenceEnergy);
    data->TM30_Rf = r3.Rf;
    data->TM30_Rg = r3.Rg;
    data->TM30_Rfi = r3.Rfi;
    data->TM30_hj_at = r3.hj.at;
    data->TM30_hj_bt = r3.hj.bt;
    data->TM30_hj_ar = r3.hj.ar;
    data->TM30_hj_br = r3.hj.br;
    data->TM30_hj_atn = r3.hj.atn;
    data->TM30_hj_btn = r3.hj.btn;
    data->TM30_hj_arn = r3.hj.arn;
    data->TM30_hj_brn = r3.hj.brn;
    data->TM30_hj_Rf = r3.hj.Rf;
    data->TM30_hj_Rcs = r3.hj.Rcs;
    data->TM30_hj_Rhs = r3.hj.Rhs;
}

CIE_UCS HSpectrometerAlgorithm::calcCieUcs(double tc)
{
    auto uvt = _cie1931->calcIsoCoordinate(tc);
    auto ref = _cieDaylight->calcRefSourceSpectrum(tc, wave());
    auto uvr = _cie1931->calcCoordinate(wave(), ref);
    auto col = _cie1931->calcColorReflectance(wave(), ref);
    auto uri = col.at(0);
    auto vri = col.at(1);
    auto Yri = col.at(2);

    CIE_UCS ucs;
    ucs.Tc = tc;
    ucs.urt = uvt[0];
    ucs.vrt = uvt[1];
    ucs.xt = uvt[2];
    ucs.yt = uvt[3];
    ucs.ur = uvr[0];
    ucs.vr = uvr[1];
    ucs.cr = uvr[6];
    ucs.dr = uvr[7];
    for (int i = 0; i < 15; i++)
    {
        ucs.Wr[i] = 25 * pow(Yri[i], 1.0/3) - 17;
        ucs.Ur[i] = 13 * ucs.Wr[i] * (uri[i] - uvr[0]);
        ucs.Vr[i] = 13 * ucs.Wr[i] * (vri[i] - uvr[1]);
    }
    return ucs;
}
