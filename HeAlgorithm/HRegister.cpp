#include "HRegister_p.h"
#include <QSettings>
#include <QDate>
#include <exception>
#include <memory>
#include <windows.h>

HE_ALGORITHM_BEGIN_NAMESPACE

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

QString HRegisterPrivate::getRegisterId()
{
    if (!registerId.isEmpty())
        return registerId;

    DWORD volumeSerialNumber;
    GetVolumeInformation(L"C:\\", nullptr, 0, &volumeSerialNumber, nullptr, nullptr, nullptr, 0);
    serialNumber =  QString::number(volumeSerialNumber, 16).toUpper();
    QString zcmNumber = "";
    bool ok;
    for (int i = 0; i < serialNumber.length(); i++)
        zcmNumber += QString::number(QString(serialNumber[i]).toInt(&ok, 16), 10);
    registerId = zcmNumber;
    return registerId;
}

bool HRegisterPrivate::isExpires()
{
    auto reg = std::make_shared<QSettings>(REGISTRY_KEY, QSettings::NativeFormat);
    trialTimes = reg->value(TRIAL_TIMES, 0).toInt();
    firstDate = reg->value(FIRST_DATE, 0).toInt();
    if (trialTimes == 0 && firstDate == 0)
        return false;

    auto expires = encryptDate(QDate::currentDate());
    return trialTimes > 60 && expires - firstDate > 30;
}

void HRegisterPrivate::trial()
{
    trialTimes++;
    auto reg = std::make_shared<QSettings>(REGISTRY_KEY, QSettings::NativeFormat);
    reg->setValue(TRIAL_TIMES, trialTimes);
    if (firstDate == 0)
        reg->setValue(FIRST_DATE, encryptDate(QDate::currentDate()));
}

HRegister::HRegister()
    : d_ptr(new HRegisterPrivate)
{
}

HRegister::HRegister(HRegisterPrivate &p)
    : d_ptr(&p)
{
}

HRegister::~HRegister()
{
}

bool HRegister::getRegisterCode(QString &registerCode)
{
    registerCode = "";
    try
    {
        auto reg = std::make_shared<QSettings>(REGISTRY_KEY, QSettings::NativeFormat);
        registerCode = reg->value(REGISTER_CODE).toString();
        return true;
    }
    catch (std::exception e)
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
        reg->setValue(REGISTER_ID, d_ptr->registerId);
        reg->setValue(SERIAL_NUMBER, d_ptr->serialNumber);
        return true;
    }
    catch (std::exception e)
    {
        return false;
    }
}

QString HRegister::getRegisterId()
{
    return d_ptr->getRegisterId();
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
    catch (std::exception ex)
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
    return d_ptr->isExpires();
}

void HRegister::trial()
{
    d_ptr->trial();
}

HE_ALGORITHM_END_NAMESPACE
