#include "HThreadDemo_p.h"
#include "HeData/ITestData.h"
#include "SlSpectrometer/HSpectrometer.h"
#include <QtGui/QPolygonF>

HThreadDemoPrivate::HThreadDemoPrivate()
{
    actionSupport << ACT_SET_INTEGRAL_TIME
                  << ACT_SET_DATA
                  << ACT_GET_SPECTRUM
                  << ACT_GET_SN
                  << ACT_GET_DATA;
    spectrometer = new HSpectrometer;
}

HThreadDemoPrivate::~HThreadDemoPrivate()
{
    delete spectrometer;
}

HThreadDemo::HThreadDemo(QObject *parent) :
    HAbstractThread(*new HThreadDemoPrivate, parent)
{
}

HThreadDemo::~HThreadDemo()
{
}

QString HThreadDemo::typeName()
{
    return "HThreadDemo";
}

QString HThreadDemo::threadInfo()
{
    return tr("线程");
}

bool HThreadDemo::handleAction(HActionType action)
{
    Q_D(HThreadDemo);

    if (action == ACT_SET_INTEGRAL_TIME)
        return d->spectrometer->setIntegralTime(d->testData->data("[积分时间]").toDouble());
    if (action == ACT_GET_SPECTRUM)
        return handleGetSpectrom();
    if (action == ACT_SET_DATA)
    {
        d->spectrometer->setStdCurve(d->testData->data("[标准数据]").value<vector<double>>());
        return true;
    }
    if (action == ACT_GET_SN)
    {
        vector<unsigned char> sn;
        if (!d->spectrometer->getSN(sn))
            return false;
        d->testData->setData("[序列号]", QVariant::fromValue(sn));
        return true;
    }
    if (action == ACT_GET_DATA)
    {
        QPolygonF p;
        for (int i = 0; i < 2048; i++)
            p << QPointF(i, d->spectrometer->pelsToWave(i));
        d->testData->setData("[像元波长]", p);
        return true;
    }
    return HAbstractThread::handleAction(action);
}

bool HThreadDemo::openProtocol()
{
    Q_D(HThreadDemo);
    if (d->spectrometer->openProtocol())
    {
        emit startFinished();
        return true;
    }
    emit startFailed("USB", tr("无法打开"));
    return false;
}

void HThreadDemo::closeProtocol()
{
    Q_D(HThreadDemo);
    d->spectrometer->closeProtocol();
    emit stopFinished();
}

bool HThreadDemo::handleGetSpectrom()
{
    Q_D(HThreadDemo);
    double percent;
    vector<double> sample;
    QPolygonF p;

    if (!d->spectrometer->getSample(sample, percent))
        return false;
    d->testData->setData("[采样比率]", percent);
    d->testData->setData("[采样值]", QVariant::fromValue(sample));

    auto data = d->spectrometer->getSpectrometerData(sample);
    if (data == nullptr)
        return true;

    for (unsigned int i = 0; i < data->Wave.size(); i++)
        p << QPointF(data->Wave.at(i), data->TestEnergyPercent.at(i));
    d->testData->setData("[能量曲线]", p);
    d->testData->setData("[峰值波长]", data->WavePeak);
    d->testData->setData("[峰值带宽]", data->Bandwidth);
    d->testData->setData("[主波长]", data->WaveDominant);
    d->testData->setData("[色纯度]", data->ColorPurity);
    d->testData->setData("[色温]", data->ColorTemperature);
    d->testData->setData("[色坐标x]", data->CoordinateX);
    d->testData->setData("[色坐标y]", data->CoordinateY);
    d->testData->setData("[色坐标u]", data->CoordinateU);
    d->testData->setData("[色坐标v]", data->CoordinateV);
    d->testData->setData("[Duv]", data->Duv);
    d->testData->setData("[红色比]", data->RatioRed);
    d->testData->setData("[蓝色比]", data->RatioBlue);
    d->testData->setData("[绿色比]", data->RatioGreen);
    d->testData->setData("[显色指数Ra]", data->RenderingIndexAvg);
    d->testData->setData("[显色指数R9]", data->RenderingIndex.at(8));
    d->testData->setData("[显色指数Rx]", QVariant::fromValue(data->RenderingIndex));
    return true;
}
