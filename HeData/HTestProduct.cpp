#include "HTestProduct_p.h"
#include "HeCore/HAppContext.h"
#include <QtCore/QSettings>

HE_BEGIN_NAMESPACE

HTestProductPrivate::HTestProductPrivate()
{
    addData("[制造厂商]", "Manufacturer");
    addData("[产品名称]", "Name");
    addData("[产品型号]", "Model");
    addData("[测试单位]", "");
    addData("[测试员]", "");
    addData("[备注]", "");
    addData("[样品编号]", 1);
    addData("[编号自增]", true);
    addData("[环境温度]", 25.0);
    addData("[环境湿度]", 60.0);
}

HTestProduct::HTestProduct() :
    HTestData(*new HTestProductPrivate)
{
}

HTestProduct::HTestProduct(HTestProductPrivate &p) :
    HTestData(p)
{
}

HTestProduct::~HTestProduct()
{
}

QVariant HTestProduct::handleOperation(QString type, QVariant value)
{
    if (type == "<编号自增>")
    {
        increase();
        return true;
    }
    if (type == "<读取配置>")
        readSettings(value.toString());
    if (type == "<写入配置>")
        writeSettings(value.toString());
    return HTestData::handleOperation(type, value);
}

void HTestProduct::increase()
{
    if (!data("[编号自增]").toBool())
        return;
    setData("[样品编号]", data("[样品编号]").toInt() + 1);
}

void HTestProduct::readSettings(QString fileName)
{
    if (fileName.isEmpty())
        fileName = HAppContext::getContextValue<QString>("Settings");
    QSettings settings(fileName, QSettings::IniFormat);
    settings.setIniCodec("utf-8");
    settings.beginGroup("ProductInfo");
    setData("[制造厂商]", settings.value("Manufacturer", "Manufacturer"));
    setData("[产品名称]", settings.value("ProductName", "Name"));
    setData("[产品型号]", settings.value("ProductModel", "Model"));
    setData("[测试单位]", settings.value("TestInstitute", ""));
    setData("[测试员]", settings.value("Tester", ""));
    setData("[备注]", settings.value("Note", ""));
    setData("[样品编号]", settings.value("SampleNumber", 1));
    setData("[环境温度]", settings.value("Temperature", 25.0));
    setData("[环境湿度]", settings.value("Humidity", 60.0));
    setData("[编号自增]", settings.value("Increase", true));
    settings.endGroup();
}

void HTestProduct::writeSettings(QString fileName)
{
    if (fileName.isEmpty())
        fileName = HAppContext::getContextValue<QString>("Settings");
    QSettings settings(fileName, QSettings::IniFormat);
    settings.setIniCodec("utf-8");
    settings.beginGroup("ProductInfo");
    settings.setValue("Manufacturer", data("[制造厂商]"));
    settings.setValue("ProductName", data("[产品名称]"));
    settings.setValue("ProductModel", data("[产品型号]"));
    settings.setValue("TestInstitute", data("[测试单位]"));
    settings.setValue("Tester", data("[测试员]"));
    settings.setValue("Note", data("[备注]"));
    settings.setValue("SampleNumber", data("[样品编号]"));
    settings.setValue("Temperature", data("[环境温度]"));
    settings.setValue("Humidity", data("[环境湿度]"));
    settings.setValue("Increase", data("[编号自增]"));
    settings.endGroup();
}

HE_END_NAMESPACE
