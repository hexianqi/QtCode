#include "HSqlGlobalInstance.h"
#include "HSql.h"
#include <QtCore/QDebug>

HE_SQL_BEGIN_NAMESPACE

QHash<QString, QString>      hashFieldType;
QHash<QString, QString>      hashFieldCreateStyle;

HSqlGlobalInstance *theInstance = HSqlGlobalInstance::instance();

QString HSql::toType(const QString &field)
{
    return hashFieldType.value(field, "[" + field + "]");
}

QStringList HSql::toType(const QStringList &field)
{
    QStringList list;
    for (const auto &f : field)
        list << toType(f);
    return list;
}

QString HSql::toField(const QString &type)
{
    return hashFieldType.key(type, type.mid(1, type.size() - 2));
}

QStringList HSql::toField(const QStringList &type)
{
    QStringList list;
    for (const auto &t : type)
        list << toField(t);
    return list;
}

QString HSql::toCreateStyle(const QString &field)
{
    return hashFieldCreateStyle.value(field, field + " [ntext]");
}

QStringList HSql::toCreateStyle(const QStringList &field)
{
    QStringList list;
    for (const auto &f : field)
        list << toCreateStyle(f);
    return list;
}

void HSqlGlobalInstance::init()
{
    initFieldType();
    initFieldCreateStyle();
}

HSqlGlobalInstance::HSqlGlobalInstance(QObject *parent) :
    QObject(parent)
{
    qInfo() << "Start Sql Instance.";
}

HSqlGlobalInstance::~HSqlGlobalInstance()
{
    qDebug() << __func__;
}

void HSqlGlobalInstance::initFieldType()
{
    hashFieldType.clear();
    hashFieldType.insert("ID",                      "[ID]");
    // 产品信息
    hashFieldType.insert("Manufacturer",            "[制造厂商]");
    hashFieldType.insert("ProductName",             "[产品名称]");
    hashFieldType.insert("ProductModel",            "[产品型号]");
    hashFieldType.insert("SampleNumber",            "[样品编号]");
    hashFieldType.insert("Tester",                  "[测试员]");
    hashFieldType.insert("TestInstitute",           "[测试单位]");
    hashFieldType.insert("Note",                    "[备注]");
    // 环境
    hashFieldType.insert("Temperature",             "[环境温度]");
    hashFieldType.insert("Humidity",                "[环境湿度]");
    // 时间
    hashFieldType.insert("TestDateTime",            "[测量日期时间]");
    hashFieldType.insert("TestDate",                "[测量日期]");
    hashFieldType.insert("TestTime",                "[测量时间]");
    // 光参数
    hashFieldType.insert("LuminousFlux",            "[光通量]");
    hashFieldType.insert("LuminousPower",           "[光功率]");
    hashFieldType.insert("LuminousEfficiency",      "[光效率]");
    // 光谱
    hashFieldType.insert("PeakWave",                "[峰值波长]");
    hashFieldType.insert("PeakBandwidth",           "[峰值带宽]");
    hashFieldType.insert("DominantWave",            "[主波长]");
    hashFieldType.insert("ColorTemperature",        "[色温]");
    hashFieldType.insert("ColorPurity",             "[色纯度]");
    hashFieldType.insert("CC_xy",                   "[色坐标]");
    hashFieldType.insert("CC_uv",                   "[色坐标uv]");
    hashFieldType.insert("CC_uvp",                  "[色坐标uvp]");
    hashFieldType.insert("CC_x",                    "[色坐标x]");
    hashFieldType.insert("CC_y",                    "[色坐标y]");
    hashFieldType.insert("CC_u",                    "[色坐标u]");
    hashFieldType.insert("CC_v",                    "[色坐标v]");
    hashFieldType.insert("CC_up",                   "[色坐标up]");
    hashFieldType.insert("CC_vp",                   "[色坐标vp]");
    hashFieldType.insert("Duv",                     "[Duv]");
    hashFieldType.insert("RedRatio",                "[红色比]");
    hashFieldType.insert("GreenRadio",              "[绿色比]");
    hashFieldType.insert("BlueRatio",               "[蓝色比]");
    hashFieldType.insert("Ra",                      "[显色指数Ra]");
    hashFieldType.insert("R9",                      "[显色指数R9]");
    hashFieldType.insert("Rx",                      "[显色指数Rx]");
    hashFieldType.insert("EnergyGraph",             "[光谱能量曲线]");
    hashFieldType.insert("LuminousFluxSpec",        "[光谱光通量]");
    // 色容差
    hashFieldType.insert("SDCM",                    "[色容差]");
    // 电
    hashFieldType.insert("OutputVoltage",           "[输出电压]");
    hashFieldType.insert("OutputCurrent",           "[输出电流]");
    hashFieldType.insert("MeasuredVoltage",         "[实测电压]");
    hashFieldType.insert("MeasuredCurrent",         "[实测电流]");
    hashFieldType.insert("ReverseVoltage",          "[反向电压]");
    hashFieldType.insert("ReverseCurrent",          "[反向漏流]");
    hashFieldType.insert("ElecPower",               "[电功率]");
    // 交流电
    hashFieldType.insert("ACVoltage",               "[交流电压]");
    hashFieldType.insert("ACCurrent",               "[交流电流]");
    hashFieldType.insert("ACPower",                 "[交流电功率]");
    hashFieldType.insert("ACFactor",                "[功率因数]");
    // 光合
    hashFieldType.insert("Photon",                  "[光量子]");
    hashFieldType.insert("Photon380_780",           "[光量子(380-780)]");
    hashFieldType.insert("Photon400_700",           "[光量子(400-700)]");
    hashFieldType.insert("Photon700_800",           "[光量子(700-800)]");
    hashFieldType.insert("PPF",                     "[光合光量子通量]");
    hashFieldType.insert("PRF",                     "[光合有效辐射通量]");
    hashFieldType.insert("PPFE",                    "[光合光子通量效率]");
    hashFieldType.insert("FluorescenceEfficiency",  "[荧光效能]");
    hashFieldType.insert("FluorescenceRatio",       "[荧光蓝光比]");

}

void HSqlGlobalInstance::initFieldCreateStyle()
{
    hashFieldCreateStyle.clear();
    hashFieldCreateStyle.insert("ID",                       "ID integer PRIMARY KEY AUTOINCREMENT NOT NULL");
    hashFieldCreateStyle.insert("TableName",                "TableName nchar(50)");
    hashFieldCreateStyle.insert("Version",                  "Version integer");
    // 产品信息
    hashFieldCreateStyle.insert("Manufacturer",             "Manufacturer nchar(50)");
    hashFieldCreateStyle.insert("ProductName",              "ProductName nchar(50)");
    hashFieldCreateStyle.insert("ProductModel",             "ProductModel nchar(50)");
    hashFieldCreateStyle.insert("SampleNumber",             "SampleNumber integer");
    hashFieldCreateStyle.insert("Tester",                   "Tester nchar(50)");
    hashFieldCreateStyle.insert("TestInstitute",            "TestInstitute nchar(50)");
    hashFieldCreateStyle.insert("Note",                     "Note nchar(500)");
    // 环境
    hashFieldCreateStyle.insert("Temperature",              "Temperature numeric(18, 1)");
    hashFieldCreateStyle.insert("Humidity",                 "Humidity numeric(18, 1)");
    // 时间
    hashFieldCreateStyle.insert("TestDateTime",             "TestDateTime datetime");
    hashFieldCreateStyle.insert("TestDate",                 "TestDate date");
    hashFieldCreateStyle.insert("TestTime",                 "TestTime time");
    // 光
    hashFieldCreateStyle.insert("LuminousFluxSpec",         "LuminousFluxSpec numeric(18, 2)");
    hashFieldCreateStyle.insert("LuminousFlux",             "LuminousFlux numeric(18, 2)");
    hashFieldCreateStyle.insert("LuminousPower",            "LuminousPower numeric(18, 2)");
    hashFieldCreateStyle.insert("LuminousEfficiency",       "LuminousEfficiency numeric(18, 2)");
    // 光谱
    hashFieldCreateStyle.insert("PeakWave",                 "PeakWave numeric(18, 1)");
    hashFieldCreateStyle.insert("PeakBandwidth",            "PeakBandwidth numeric(18, 1)");
    hashFieldCreateStyle.insert("DominantWave",             "DominantWave numeric(18, 1)");
    hashFieldCreateStyle.insert("ColorTemperature",         "ColorTemperature numeric(18, 0)");
    hashFieldCreateStyle.insert("ColorPurity",              "ColorPurity numeric(18, 3)");
    hashFieldCreateStyle.insert("CC_x",                     "CC_x numeric(18, 4)");
    hashFieldCreateStyle.insert("CC_y",                     "CC_y numeric(18, 4)");
    hashFieldCreateStyle.insert("CC_u",                     "CC_u numeric(18, 4)");
    hashFieldCreateStyle.insert("CC_v",                     "CC_v numeric(18, 4)");
    hashFieldCreateStyle.insert("CC_up",                    "CC_up numeric(18, 4)");
    hashFieldCreateStyle.insert("CC_vp",                    "CC_vp numeric(18, 4)");
    hashFieldCreateStyle.insert("Duv",                      "Duv numeric(18, 3)");
    hashFieldCreateStyle.insert("RedRatio",                 "RedRatio numeric(18, 1)");
    hashFieldCreateStyle.insert("GreenRadio",               "GreenRadio numeric(18, 1)");
    hashFieldCreateStyle.insert("BlueRatio",                "BlueRatio numeric(18, 1)");
    hashFieldCreateStyle.insert("Ra",                       "Ra numeric(18, 2)");
    hashFieldCreateStyle.insert("R9",                       "R9 numeric(18, 2)");
    hashFieldCreateStyle.insert("Rx",                       "Rx nchar(200)");
    hashFieldCreateStyle.insert("EnergyGraph",              "EnergyGraph ntext");
    // 色容差
    hashFieldCreateStyle.insert("SDCM",                     "SDCM numeric(18, 1)");
    // 电
    hashFieldCreateStyle.insert("OutputVoltage",            "OutputVoltage numeric(18, 2)");
    hashFieldCreateStyle.insert("OutputCurrent",            "OutputCurrent numeric(18, 2)");
    hashFieldCreateStyle.insert("MeasuredVoltage",          "MeasuredVoltage numeric(18, 2)");
    hashFieldCreateStyle.insert("MeasuredCurrent",          "MeasuredCurrent numeric(18, 2)");
    hashFieldCreateStyle.insert("ReverseVoltage",           "ReverseVoltage numeric(18, 2)");
    hashFieldCreateStyle.insert("ReverseCurrent",           "ReverseCurrent numeric(18, 2)");
    hashFieldCreateStyle.insert("ElecPower",                "ElecPower numeric(18, 2)");
    // 交流电
    hashFieldCreateStyle.insert("ACCurrent",                "ACCurrent numeric(18, 2)");
    hashFieldCreateStyle.insert("ACVoltage",                "ACVoltage numeric(18, 2)");
    hashFieldCreateStyle.insert("ACPower",                  "ACPower numeric(18, 2)");
    hashFieldCreateStyle.insert("ACFactor",                 "ACFactor numeric(18, 2)");
    // 光合
    hashFieldCreateStyle.insert("Photon",                   "Photon numeric(18, 3)");
    hashFieldCreateStyle.insert("Photon380_780",            "Photon380_780 numeric(18, 3)");
    hashFieldCreateStyle.insert("Photon400_700",            "Photon400_700 numeric(18, 3)");
    hashFieldCreateStyle.insert("Photon700_800",            "Photon700_800 numeric(18, 3)");
    hashFieldCreateStyle.insert("PPF",                      "PPF numeric(18, 3)");
    hashFieldCreateStyle.insert("PRF",                      "PRF numeric(18, 3)");
    hashFieldCreateStyle.insert("PPFE",                     "PPFE numeric(18, 3)");
    hashFieldCreateStyle.insert("FluorescenceEfficiency",   "FluorescenceEfficiency numeric(18, 3)");
    hashFieldCreateStyle.insert("FluorescenceRatio",        "FluorescenceRatio numeric(18, 3)");
}

HE_SQL_END_NAMESPACE
