#include "HRegister.h"
#include <QString>
#include <QSettings>
#include <QDate>
#include <exception>
#include <memory>
#include <windows.h>

using namespace std;
using namespace He::Algorithm;

const QString REGISTRY_KEY = "HKEY_CURRENT_USER\\Software\\ebangTest";
const QString REGISTER_ID = "banben";
const QString REGISTER_CODE = "xulie";
const QString SERIAL_NUMBER = "ma_no";
const QString TRIAL_TIMES = "trti";
const QString FIRST_DATE = "fida";

void splitRegisterId(QString registerId, int &i1, int &i2)
{
    if (registerId.length() < 10)
    {
    //    int lenght = registerId.length();
        for (int i = 1; i <= 10 - registerId.length(); i++)
            registerId = registerId + QString::number(i);
    }
    if (registerId.length() > 10)
        registerId = registerId.left(10);

    i1 = registerId.left(5).toInt();
    i2 = registerId.right(5).toInt();
}

int encryptDate(QDate value)
{
    return (value.year() - 2010) * 430 + value.month() * 32 + value.day();
}

HRegister::HRegister()
{
    _registerId = "";
    _serialNumber = "";
    _trialTimes = 0;
    _firstDate = 0;
}

bool HRegister::getRegisterCode(QString &registerCode)
{
    registerCode = "";
    try
    {
        auto reg = make_shared<QSettings>(REGISTRY_KEY, QSettings::NativeFormat);
        registerCode = reg->value(REGISTER_CODE).toString();
        return true;
    }
    catch (exception e)
    {
        return false;
    }
}

bool HRegister::setRegisterCode(QString registerCode)
{
    try
    {
        auto reg = std::make_shared<QSettings>(REGISTRY_KEY, QSettings::NativeFormat);
        reg->setValue(REGISTER_CODE, registerCode);
        reg->setValue(REGISTER_ID, _registerId);
        reg->setValue(SERIAL_NUMBER, _serialNumber);
        return true;
    }
    catch (exception e)
    {
        return false;
    }
}

QString HRegister::getRegisterId()
{
    if (_registerId != nullptr)
        return _registerId;

    DWORD volumeSerialNumber;
    GetVolumeInformation(L"C:\\", nullptr, 0, &volumeSerialNumber, nullptr, nullptr, nullptr, 0);
    _serialNumber =  QString::number(volumeSerialNumber, 16).toUpper();
    QString zcmNumber = "";
    bool ok;
    for (int i = 0; i < _serialNumber.length(); i++)
        zcmNumber += QString::number(QString(_serialNumber[i]).toInt(&ok, 16), 10);
    _registerId = zcmNumber;
    return _registerId;
}

bool HRegister::checkRegisterCode()
{
    QString registerCode;
    if (!getRegisterCode(registerCode))
        return false;
    return checkRegisterCode(getRegisterId(), registerCode);
}

bool HRegister::checkRegisterCode(QString registerId, QString registerCode)
{
    try
    {
        auto encryptNum = encrypt(registerId);
        return encryptNum == registerCode;
    }
    catch (exception ex)
    {
        return false;
    }
}

QString HRegister::encrypt(QString registerId)
{
    int i1, i2;
    splitRegisterId(registerId, i1, i2);
    registerId = QString::number(i1 * 5918 + i2 * 5858);
    splitRegisterId(registerId, i1, i2);
    return QString::number(i1 ^ i2);
}

bool HRegister::isExpires()
{
    auto reg = make_shared<QSettings>(REGISTRY_KEY, QSettings::NativeFormat);
    _trialTimes = reg->value(TRIAL_TIMES, 0).toInt();
    _firstDate = reg->value(FIRST_DATE, 0).toInt();
    if (_trialTimes == 0 && _firstDate == 0)
        return false;

    auto expires = encryptDate(QDate::currentDate());
    return _trialTimes > 60 && expires - _firstDate > 30;
}

void HRegister::trial()
{
    _trialTimes++;
    auto reg = std::make_shared<QSettings>(REGISTRY_KEY, QSettings::NativeFormat);
    reg->setValue(TRIAL_TIMES, _trialTimes);
    if (_firstDate == 0)
        reg->setValue(FIRST_DATE, encryptDate(QDate::currentDate()));
}
