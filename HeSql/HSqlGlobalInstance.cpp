#include "HSqlGlobalInstance.h"
#include "HSql.h"
#include <QDebug>

HE_SQL_BEGIN_NAMESPACE

QHash<QString, QString>      hashFieldType;
QHash<QString, QString>      hashFieldCreateStyle;

QString toCreateStyle(QString field)
{
    return hashFieldCreateStyle.value(field, field + " [ntext]");
}

QStringList toCreateStyle(QStringList field)
{
    QStringList list;
    for (auto f : field)
        list << toCreateStyle(field);
    return list;
}

HSqlGlobalInstance *theInstance = HSqlGlobalInstance::instance();

HSqlGlobalInstance::HSqlGlobalInstance(QObject *parent) :
    QObject(parent)
{
    qDebug() << __func__;
    initFieldType();
    initFieldCreateStyle();
}

HSqlGlobalInstance::~HSqlGlobalInstance()
{
    qDebug() << __func__;
}

void HSqlGlobalInstance::initFieldType()
{
    hashFieldType.clear();
    hashFieldType.insert("ID",                           "[ID]");
//    mapFieldType.insert(tr("Manufacturer"),                 tr("[制造厂商]"));
//    mapFieldType.insert(tr("ProductName"),                  tr("[产品名称]"));
//    mapFieldType.insert(tr("ProductModel"),                 tr("[产品型号]"));
//    mapFieldType.insert(tr("SampleNumber"),                 tr("[样品编号]"));
//    mapFieldType.insert(tr("Tester"),                       tr("[测试员]"));
//    mapFieldType.insert(tr("TestInstitute"),                tr("[测试单位]"));
//    mapFieldType.insert(tr("Note"),                         tr("[备注]"));
//    mapFieldType.insert(tr("Temperature"),                  tr("[环境温度]"));
//    mapFieldType.insert(tr("Humidity"),                     tr("[环境湿度]"));
//    mapFieldType.insert(tr("TestDateTime"),                 tr("[测量日期时间]"));
//    mapFieldType.insert(tr("TestDate"),                     tr("[测量日期]"));
//    mapFieldType.insert(tr("TestTime"),                     tr("[测量时间]"));
//    mapFieldType.insert(tr("ForwardCurrent"),               tr("[正向电流]"));
//    mapFieldType.insert(tr("ForwardVoltage"),               tr("[正向电压]"));
//    mapFieldType.insert(tr("ReverseVoltage"),               tr("[反向电压]"));
//    mapFieldType.insert(tr("ReverseCurrent"),               tr("[反向漏流]"));
//    mapFieldType.insert(tr("FeedbackCurrent"),              tr("[回溯电流]"));
//    mapFieldType.insert(tr("ElecPower"),                    tr("[电功率]"));
//    mapFieldType.insert(tr("ACCurrent"),                    tr("[交流电流]"));
//    mapFieldType.insert(tr("ACVoltage"),                    tr("[交流电压]"));
//    mapFieldType.insert(tr("ACPower"),                      tr("[交流电功率]"));
//    mapFieldType.insert(tr("ACFactor"),                     tr("[功率因素]"));
//    mapFieldType.insert(tr("LuminousFlux"),                 tr("[光通量]"));
//    mapFieldType.insert(tr("LuminousPower"),                tr("[光功率]"));
//    mapFieldType.insert(tr("LuminousEfficiency"),           tr("[光效]"));
//    mapFieldType.insert(tr("PeakWave"),                     tr("[峰值波长]"));
//    mapFieldType.insert(tr("PeakBandwidth"),                tr("[峰值带宽]"));
//    mapFieldType.insert(tr("DominantWave"),                 tr("[主波长]"));
//    mapFieldType.insert(tr("ColorTemperature"),             tr("[色温]"));
//    mapFieldType.insert(tr("ColorPurity"),                  tr("[色纯度]"));
//    mapFieldType.insert(tr("CC_xy"),                        tr("[色坐标]"));
//    mapFieldType.insert(tr("CC_uv"),                        tr("[色坐标uv]"));
//    mapFieldType.insert(tr("CC_uvp"),                       tr("[色坐标uvp]"));
//    mapFieldType.insert(tr("CC_x"),                         tr("[色坐标x]"));
//    mapFieldType.insert(tr("CC_y"),                         tr("[色坐标y]"));
//    mapFieldType.insert(tr("CC_u"),                         tr("[色坐标u]"));
//    mapFieldType.insert(tr("CC_v"),                         tr("[色坐标v]"));
//    mapFieldType.insert(tr("CC_up"),                        tr("[色坐标up]"));
//    mapFieldType.insert(tr("CC_vp"),                        tr("[色坐标vp]"));
//    mapFieldType.insert(tr("Duv"),                          tr("[Duv]"));
//    mapFieldType.insert(tr("RedRatio"),                     tr("[红色比]"));
//    mapFieldType.insert(tr("GreenRadio"),                   tr("[绿色比]"));
//    mapFieldType.insert(tr("BlueRatio"),                    tr("[蓝色比]"));
//    mapFieldType.insert(tr("Ra"),                           tr("[显色指数]"));
//    mapFieldType.insert(tr("Rx"),                           tr("[显色指数Rx]"));
//    mapFieldType.insert(tr("EnergyGraph"),                  tr("[光谱能量数据]"));


//    mapFieldType.insert(tr("OutputCurrent"),                tr("[输出电流]"));
//    mapFieldType.insert(tr("OutputVoltage"),                tr("[输出电压]"));
//    mapFieldType.insert(tr("ActualCurrent"),                tr("[实测电流]"));
//    mapFieldType.insert(tr("ActualVoltage"),                tr("[实测电压]"));
//    mapFieldType.insert(tr("LuminousFluxSpec"),             tr("[光谱光通量]"));

}

void HSqlGlobalInstance::initFieldCreateStyle()
{
//    mapFieldCreateStyle.clear();
//    mapFieldCreateStyle.insert(tr("ID"),                    tr("ID integer PRIMARY KEY AUTOINCREMENT NOT NULL"));

//    mapFieldCreateStyle.insert(tr("Manufacturer"),          tr("Manufacturer nchar(50)"));
//    mapFieldCreateStyle.insert(tr("ProductName"),           tr("ProductName nchar(50)"));
//    mapFieldCreateStyle.insert(tr("ProductModel"),          tr("ProductModel nchar(50)"));
//    mapFieldCreateStyle.insert(tr("SampleNumber"),          tr("SampleNumber integer"));
//    mapFieldCreateStyle.insert(tr("Tester"),                tr("Tester nchar(50)"));
//    mapFieldCreateStyle.insert(tr("TestInstitute"),         tr("TestInstitute nchar(50)"));
//    mapFieldCreateStyle.insert(tr("Note"),                  tr("Note nchar(500)"));
//    mapFieldCreateStyle.insert(tr("Temperature"),           tr("Temperature numeric(18, 1)"));
//    mapFieldCreateStyle.insert(tr("Humidity"),              tr("Humidity numeric(18, 1)"));

//    mapFieldCreateStyle.insert(tr("TestDateTime"),          tr("TestDateTime datetime"));
//    mapFieldCreateStyle.insert(tr("TestDate"),              tr("TestDate date"));
//    mapFieldCreateStyle.insert(tr("TestTime"),              tr("TestTime time"));

//    mapFieldCreateStyle.insert(tr("ForwardCurrent"),        tr("ForwardCurrent numeric(18, 2)"));
//    mapFieldCreateStyle.insert(tr("ForwardVoltage"),        tr("ForwardVoltage numeric(18, 2)"));
//    mapFieldCreateStyle.insert(tr("ReverseVoltage"),        tr("ReverseVoltage numeric(18, 2)"));
//    mapFieldCreateStyle.insert(tr("ReverseCurrent"),        tr("ReverseCurrent numeric(18, 2)"));
//    mapFieldCreateStyle.insert(tr("ElecPower"),             tr("ElecPower numeric(18, 2)"));
//    mapFieldCreateStyle.insert(tr("ACCurrent"),             tr("ACCurrent numeric(18, 2)"));
//    mapFieldCreateStyle.insert(tr("ACVoltage"),             tr("ACVoltage numeric(18, 2)"));
//    mapFieldCreateStyle.insert(tr("ACPower"),               tr("ACPower numeric(18, 2)"));
//    mapFieldCreateStyle.insert(tr("ACFactor"),              tr("ACFactor numeric(18, 2)"));
//    mapFieldCreateStyle.insert(tr("OutputCurrent"),         tr("OutputCurrent numeric(18, 2)"));
//    mapFieldCreateStyle.insert(tr("OutputVoltage"),         tr("OutputVoltage numeric(18, 2)"));
//    mapFieldCreateStyle.insert(tr("ActualCurrent"),         tr("ActualCurrent numeric(18, 2)"));
//    mapFieldCreateStyle.insert(tr("ActualVoltage"),         tr("ActualVoltage numeric(18, 2)"));

//    mapFieldCreateStyle.insert(tr("LuminousFlux"),          tr("LuminousFlux numeric(18, 2)"));
//    mapFieldCreateStyle.insert(tr("LuminousPower"),         tr("LuminousPower numeric(18, 2)"));
//    mapFieldCreateStyle.insert(tr("LuminousEfficiency"),    tr("LuminousEfficiency numeric(18, 2)"));
//    mapFieldCreateStyle.insert(tr("LuminousFluxSpec"),      tr("LuminousFluxSpec numeric(18, 2)"));

//    mapFieldCreateStyle.insert(tr("PeakWave"),              tr("PeakWave numeric(18, 1)"));
//    mapFieldCreateStyle.insert(tr("PeakBandwidth"),         tr("PeakBandwidth numeric(18, 1)"));
//    mapFieldCreateStyle.insert(tr("DominantWave"),          tr("DominantWave numeric(18, 1)"));
//    mapFieldCreateStyle.insert(tr("ColorTemperature"),      tr("ColorTemperature numeric(18, 0)"));
//    mapFieldCreateStyle.insert(tr("ColorPurity"),           tr("ColorPurity numeric(18, 3)"));
//    mapFieldCreateStyle.insert(tr("CC_x"),                  tr("CC_x numeric(18, 4)"));
//    mapFieldCreateStyle.insert(tr("CC_y"),                  tr("CC_y numeric(18, 4)"));
//    mapFieldCreateStyle.insert(tr("CC_u"),                  tr("CC_u numeric(18, 4)"));
//    mapFieldCreateStyle.insert(tr("CC_v"),                  tr("CC_v numeric(18, 4)"));
//    mapFieldCreateStyle.insert(tr("CC_up"),                 tr("CC_up numeric(18, 4)"));
//    mapFieldCreateStyle.insert(tr("CC_vp"),                 tr("CC_vp numeric(18, 4)"));
//    mapFieldCreateStyle.insert(tr("Duv"),                   tr("Duv numeric(18, 3)"));
//    mapFieldCreateStyle.insert(tr("RedRatio"),              tr("RedRatio numeric(18, 1)"));
//    mapFieldCreateStyle.insert(tr("GreenRadio"),            tr("GreenRadio numeric(18, 1)"));
//    mapFieldCreateStyle.insert(tr("BlueRatio"),             tr("BlueRatio numeric(18, 1)"));
//    mapFieldCreateStyle.insert(tr("Ra"),                    tr("Ra numeric(18, 2)"));
//    mapFieldCreateStyle.insert(tr("Rx"),                    tr("Rx nchar(200)"));
//    mapFieldCreateStyle.insert(tr("EnergyGraph"),           tr("EnergyGraph ntext"));

}

HE_SQL_END_NAMESPACE
