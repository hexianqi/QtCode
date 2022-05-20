#include "HSqlGlobalInstance.h"
#include "HSql.h"
#include <QtCore/QDebug>

HE_BEGIN_NAMESPACE

QHash<QString, QString>      hashFieldType;
QHash<QString, QString>      hashFieldCreateStyle;
QHash<QString, QStringList>  hashFieldGroup;

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

QStringList HSql::membership(const QString &name)
{
    return hashFieldGroup.value(name);
}

QStringList HSql::membership(const QStringList &name)
{
    QStringList list;
    for (const auto &t : name)
        list << hashFieldGroup.value(t);
    return list;
}

void HSqlGlobalInstance::initialize()
{
    if (_initialized)
        return;
    initFieldType();
    initFieldCreateStyle();
    initFieldGroup();
    _initialized = true;
}

HSqlGlobalInstance::HSqlGlobalInstance(QObject *parent) :
    QObject(parent)
{
    qInfo() << "Start Sql Instance.";
}

HSqlGlobalInstance::~HSqlGlobalInstance()
{
    qInfo() << "Stop Sql Instance.";
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
    hashFieldType.insert("LuminousIntensity",       "[光强度]");
    hashFieldType.insert("LuminousFlux",            "[光通量]");
    hashFieldType.insert("LuminousPower",           "[光功率]");
    hashFieldType.insert("LuminousEfficiency",      "[光效率]");
    // 光谱
    hashFieldType.insert("PeakWave",                "[峰值波长]");
    hashFieldType.insert("PeakBandwidth",           "[峰值带宽]");
    hashFieldType.insert("DominantWave",            "[主波长]");
    hashFieldType.insert("ColorTemperature",        "[色温]");
    hashFieldType.insert("ColorPurity",             "[色纯度]");
    hashFieldType.insert("Duv",                     "[Duv]");
    hashFieldType.insert("LuminousFluxSpec",        "[光谱光通量]");
    hashFieldType.insert("CC_xy",                   "[色坐标]");
    hashFieldType.insert("CC_uv",                   "[色坐标uv]");
    hashFieldType.insert("CC_uvp",                  "[色坐标uvp]");
    hashFieldType.insert("CC_x",                    "[色坐标x]");
    hashFieldType.insert("CC_y",                    "[色坐标y]");
    hashFieldType.insert("CC_u",                    "[色坐标u]");
    hashFieldType.insert("CC_v",                    "[色坐标v]");
    hashFieldType.insert("CC_up",                   "[色坐标up]");
    hashFieldType.insert("CC_vp",                   "[色坐标vp]");
    hashFieldType.insert("RedRatio",                "[红色比]");
    hashFieldType.insert("GreenRadio",              "[绿色比]");
    hashFieldType.insert("BlueRatio",               "[蓝色比]");
    hashFieldType.insert("Ra",                      "[显色指数Ra]");
    hashFieldType.insert("R9",                      "[显色指数R9]");
    hashFieldType.insert("Rx",                      "[显色指数Rx]");
    hashFieldType.insert("EnergyGraph",             "[光谱能量曲线]");
    hashFieldType.insert("ReflectGraph",            "[光谱反射曲线]");
    // 色容差
    hashFieldType.insert("SDCMDetail",              "[色容差标准]");
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
    // 光强角
    hashFieldType.insert("ADLI_LIMax",              "[最大光强度]");
    hashFieldType.insert("ADLI_LINormal",           "[法向光强度]");
    hashFieldType.insert("ADLI_LF",                 "[角度光通量]");
    hashFieldType.insert("ADLI_AngleMax",           "[最大光强度角]");
    hashFieldType.insert("ADLI_AngleHalfLeft",      "[左半光强度角]");
    hashFieldType.insert("ADLI_AngleHalfRight",     "[右半光强度角]");
    hashFieldType.insert("ADLI_AngleHalfOff",       "[半光强度夹角]");
    hashFieldType.insert("ADLI_AngleFifthLeft",     "[左1/5光强度角]");
    hashFieldType.insert("ADLI_AngleFifthRight",    "[右1/5光强度角]");
    hashFieldType.insert("ADLI_AngleFifthOff",      "[1/5光强度夹角]");
    hashFieldType.insert("ADLI_Graph",              "[光强角度分布]");
    // TM30
    hashFieldType.insert("TM30_Rf",                 "[TM30_Rf]");
    hashFieldType.insert("TM30_Rg",                 "[TM30_Rg]");
    hashFieldType.insert("TM30_Rfi",                "[TM30_Rfi]");
    hashFieldType.insert("TM30_hj_Rf",              "[TM30_hj_Rf]");
    hashFieldType.insert("TM30_hj_Rcs",             "[TM30_hj_Rcs]");
    hashFieldType.insert("TM30_hj_Rhs",             "[TM30_hj_Rhs]");
    hashFieldType.insert("TM30_hj_at",              "[TM30_hj_at]");
    hashFieldType.insert("TM30_hj_bt",              "[TM30_hj_bt]");
    hashFieldType.insert("TM30_hj_ar",              "[TM30_hj_ar]");
    hashFieldType.insert("TM30_hj_br",              "[TM30_hj_br]");
    hashFieldType.insert("TM30_hj_atn",             "[TM30_hj_atn]");
    hashFieldType.insert("TM30_hj_btn",             "[TM30_hj_btn]");
    hashFieldType.insert("TM30_hj_arn",             "[TM30_hj_arn]");
    hashFieldType.insert("TM30_hj_brn",             "[TM30_hj_brn]");

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
    hashFieldCreateStyle.insert("LuminousIntensity",        "LuminousIntensity numeric(18, 2)");
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
    hashFieldCreateStyle.insert("LuminousFluxSpec",         "LuminousFluxSpec numeric(18, 2)");
    hashFieldCreateStyle.insert("EnergyGraph",              "EnergyGraph ntext");
    hashFieldCreateStyle.insert("ReflectGraph",             "ReflectGraph ntext");
    // 色容差
    hashFieldCreateStyle.insert("SDCMDetail",               "SDCMDetail nchar(1000)");
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
    // 光强角
    hashFieldCreateStyle.insert("ADLI_LIMax",               "ADLI_LIMax numeric(18, 3)");
    hashFieldCreateStyle.insert("ADLI_LINormal",            "ADLI_LINormal numeric(18, 3)");
    hashFieldCreateStyle.insert("ADLI_LF",                  "ADLI_LF numeric(18, 3)");
    hashFieldCreateStyle.insert("ADLI_AngleMax",            "ADLI_AngleMax numeric(18, 1)");
    hashFieldCreateStyle.insert("ADLI_AngleHalfLeft",       "ADLI_AngleHalfLeft numeric(18, 1)");
    hashFieldCreateStyle.insert("ADLI_AngleHalfRight",      "ADLI_AngleHalfRight numeric(18, 1)");
    hashFieldCreateStyle.insert("ADLI_AngleHalfOff",        "ADLI_AngleHalfOff numeric(18, 1)");
    hashFieldCreateStyle.insert("ADLI_AngleFifthLeft",      "ADLI_AngleFifthLeft numeric(18, 1)");
    hashFieldCreateStyle.insert("ADLI_AngleFifthRight",     "ADLI_AngleFifthRight numeric(18, 1)");
    hashFieldCreateStyle.insert("ADLI_AngleFifthOff",       "ADLI_AngleFifthOff numeric(18, 1)");
    hashFieldCreateStyle.insert("ADLI_Graph",               "ADLI_Graph ntext");
    // TM30
    hashFieldCreateStyle.insert("TM30_Rf",                 "TM30_Rf numeric(18, 2)");
    hashFieldCreateStyle.insert("TM30_Rg",                 "TM30_Rg numeric(18, 2)");
    hashFieldCreateStyle.insert("TM30_Rfi",                "TM30_Rfi nchar(1000)");
    hashFieldCreateStyle.insert("TM30_hj_Rf",              "TM30_hj_Rf nchar(200)");
    hashFieldCreateStyle.insert("TM30_hj_Rcs",             "TM30_hj_Rcs nchar(200)");
    hashFieldCreateStyle.insert("TM30_hj_Rhs",             "TM30_hj_Rhs nchar(200)");
    hashFieldCreateStyle.insert("TM30_hj_at",              "TM30_hj_at nchar(200)");
    hashFieldCreateStyle.insert("TM30_hj_bt",              "TM30_hj_bt nchar(200)");
    hashFieldCreateStyle.insert("TM30_hj_ar",              "TM30_hj_ar nchar(200)");
    hashFieldCreateStyle.insert("TM30_hj_br",              "TM30_hj_br nchar(200)");
    hashFieldCreateStyle.insert("TM30_hj_atn",             "TM30_hj_atn nchar(200)");
    hashFieldCreateStyle.insert("TM30_hj_btn",             "TM30_hj_btn nchar(200)");
    hashFieldCreateStyle.insert("TM30_hj_arn",             "TM30_hj_arn nchar(200)");
    hashFieldCreateStyle.insert("TM30_hj_brn",             "TM30_hj_brn nchar(200)");
}

void HSqlGlobalInstance::initFieldGroup()
{
    // |产品信息2|      - [Note]
    // |产品信息3|      - [ProductName][TestInstitute][Note]
    // |光谱信息2|      - [CC_u][CC_v]
    // |光谱信息3|      - [CC_u][CC_v][LuminousFluxSpec]
    // |光谱信息4|      - [CC_u][CC_v][EnergyGraph][ReflectGraph]
    // |光谱信息5|      - [CC_u][CC_v][LuminousFluxSpec][EnergyGraph][ReflectGraph]
    // |光度信息2|      - [LuminousIntensity]
    // |光度信息3|      = [LuminousPower][LuminousEfficiency]
    // |光度信息4|      = [LuminousPower]
    // |色容差信息2|    - [SDCMDetail]
    // |直流电信息2|    - [ReverseVoltage][ReverseCurrent]
    // |TM30信息2|      = [TM30_Rf][TM30_Rg]
    // |TM30信息3|      - [TM30_Rf][TM30_Rg]
    // |光强角度信息2|  - [ADLI_Graph]

    hashFieldGroup.insert("|产品信息|",      QStringList() << "Manufacturer" << "ProductName" << "ProductModel"  << "SampleNumber" << "TestInstitute" << "Tester" << "Note");
    hashFieldGroup.insert("|产品信息2|",     QStringList() << "Manufacturer" << "ProductName" << "ProductModel"  << "SampleNumber" << "TestInstitute" << "Tester");
    hashFieldGroup.insert("|产品信息3|",     QStringList() << "Manufacturer" << "ProductModel" << "SampleNumber" << "Tester");
    hashFieldGroup.insert("|环境信息|",      QStringList() << "Temperature" << "Humidity");
    hashFieldGroup.insert("|时间信息|",      QStringList() << "TestDateTime");
    hashFieldGroup.insert("|时间信息2|",     QStringList() << "TestDate" << "TestTime");
    hashFieldGroup.insert("|光谱信息|",      QStringList() << "PeakWave" << "PeakBandwidth" << "DominantWave"
                                                           << "CC_x" << "CC_y" << "CC_u" << "CC_v" << "CC_up" << "CC_vp"
                                                           << "ColorTemperature" << "ColorPurity" << "Duv" << "LuminousFluxSpec"
                                                           << "RedRatio" << "GreenRadio" << "BlueRatio"
                                                           << "Ra" << "R9" << "Rx"
                                                           << "EnergyGraph" << "ReflectGraph");
    hashFieldGroup.insert("|光谱信息2|",     QStringList() << "PeakWave" << "PeakBandwidth" << "DominantWave"
                                                           << "CC_x" << "CC_y" << "CC_up" << "CC_vp"
                                                           << "ColorTemperature" << "ColorPurity" << "Duv" << "LuminousFluxSpec"
                                                           << "RedRatio" << "GreenRadio" << "BlueRatio"
                                                           << "Ra" << "R9" << "Rx"
                                                           << "EnergyGraph" << "ReflectGraph");
    hashFieldGroup.insert("|光谱信息3|",     QStringList() << "PeakWave" << "PeakBandwidth" << "DominantWave"
                                                           << "CC_x" << "CC_y" << "CC_up" << "CC_vp"
                                                           << "ColorTemperature" << "ColorPurity" << "Duv"
                                                           << "RedRatio" << "GreenRadio" << "BlueRatio"
                                                           << "Ra" << "R9" << "Rx"
                                                           << "EnergyGraph" << "ReflectGraph");
    hashFieldGroup.insert("|光谱信息4|",     QStringList() << "PeakWave" << "PeakBandwidth" << "DominantWave"
                                                           << "CC_x" << "CC_y" << "CC_up" << "CC_vp"
                                                           << "ColorTemperature" << "ColorPurity" << "Duv" << "LuminousFluxSpec"
                                                           << "RedRatio" << "GreenRadio" << "BlueRatio"
                                                           << "Ra" << "R9" << "Rx");
    hashFieldGroup.insert("|光谱信息5|",     QStringList() << "PeakWave" << "PeakBandwidth" << "DominantWave"
                                                           << "CC_x" << "CC_y" << "CC_up" << "CC_vp"
                                                           << "ColorTemperature" << "ColorPurity" << "Duv"
                                                           << "RedRatio" << "GreenRadio" << "BlueRatio"
                                                           << "Ra" << "R9" << "Rx");
    hashFieldGroup.insert("|光度信息|",      QStringList() << "LuminousIntensity" << "LuminousFlux" << "LuminousPower" << "LuminousEfficiency");
    hashFieldGroup.insert("|光度信息2|",     QStringList() << "LuminousFlux" << "LuminousPower" << "LuminousEfficiency");
    hashFieldGroup.insert("|光度信息3|",     QStringList() << "LuminousPower" << "LuminousEfficiency");
    hashFieldGroup.insert("|光度信息4|",     QStringList() << "LuminousPower");
    hashFieldGroup.insert("|光合信息|",      QStringList() << "Photon380_780" << "Photon400_700" << "Photon700_800"
                                                           << "PPF" << "PRF" << "PPFE"
                                                           << "FluorescenceEfficiency" << "FluorescenceRatio");
    hashFieldGroup.insert("|色容差信息|",    QStringList() << "SDCMDetail" << "SDCM");
    hashFieldGroup.insert("|色容差信息2|",   QStringList() << "SDCM");
    hashFieldGroup.insert("|TM30信息|",      QStringList() << "TM30_Rf" << "TM30_Rg" << "TM30_Rfi"
                                                           << "TM30_hj_Rf" << "TM30_hj_Rcs" << "TM30_hj_Rhs"
                                                           << "TM30_hj_at" << "TM30_hj_bt" << "TM30_hj_ar" << "TM30_hj_br"
                                                           << "TM30_hj_atn" << "TM30_hj_btn" << "TM30_hj_arn" << "TM30_hj_brn");
    hashFieldGroup.insert("|TM30信息2|",     QStringList() << "TM30_Rf" << "TM30_Rg");
    hashFieldGroup.insert("|TM30信息3|",     QStringList() << "TM30_Rfi"
                                                           << "TM30_hj_Rf" << "TM30_hj_Rcs" << "TM30_hj_Rhs"
                                                           << "TM30_hj_at" << "TM30_hj_bt" << "TM30_hj_ar" << "TM30_hj_br"
                                                           << "TM30_hj_atn" << "TM30_hj_btn" << "TM30_hj_arn" << "TM30_hj_brn");
    hashFieldGroup.insert("|直流电信息|",    QStringList() << "OutputVoltage" << "MeasuredVoltage" << "OutputCurrent" << "MeasuredCurrent" << "ReverseVoltage" << "ReverseCurrent" << "ElecPower");
    hashFieldGroup.insert("|直流电信息2|",   QStringList() << "OutputVoltage" << "MeasuredVoltage" << "OutputCurrent" << "MeasuredCurrent" << "ElecPower");
    hashFieldGroup.insert("|交流电信息|",    QStringList() << "ACVoltage" << "ACCurrent" << "ACPower" << "ACFactor");

    hashFieldGroup.insert("|光强角度信息|",  QStringList() << "ADLI_LIMax" << "ADLI_LINormal" << "ADLI_LF" << "ADLI_AngleMax"
                                                           << "ADLI_AngleHalfLeft" << "ADLI_AngleHalfRight" << "ADLI_AngleHalfOff"
                                                           << "ADLI_AngleFifthLeft" << "ADLI_AngleFifthRight" << "ADLI_AngleFifthOff"
                                                           << "ADLI_Graph");
    hashFieldGroup.insert("|光强角度信息2|", QStringList() << "ADLI_LIMax" << "ADLI_LINormal" << "ADLI_LF" << "ADLI_AngleMax"
                                                           << "ADLI_AngleHalfLeft" << "ADLI_AngleHalfRight" << "ADLI_AngleHalfOff"
                                                           << "ADLI_AngleFifthLeft" << "ADLI_AngleFifthRight" << "ADLI_AngleFifthOff");
    // 数据格式
    hashFieldGroup.insert("|多边形格式|",    QStringList() << "EnergyGraph" << "ReflectGraph" << "ADLI_Graph");
    hashFieldGroup.insert("|列表格式|",      QStringList() << "TM30_Rfi" << "TM30_hj_Rf" << "TM30_hj_Rcs" << "TM30_hj_Rhs"
                                                           << "TM30_hj_at" << "TM30_hj_bt" << "TM30_hj_ar" << "TM30_hj_br"
                                                           << "TM30_hj_atn" << "TM30_hj_btn" << "TM30_hj_arn" << "TM30_hj_brn");
}

HE_END_NAMESPACE
