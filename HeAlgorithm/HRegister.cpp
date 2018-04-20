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

class HRegisterPrivate
{
    Q_DECLARE_PUBLIC(HRegister)

public:
    HRegisterPrivate(HRegister *q)
        : q_ptr(q)
    {
    }

public:
    HRegister *q_ptr;
    QString _registerId = "";
    QString _serialNumber = "";
    int _trialTimes = 0;
    int _firstDate = 0;
};

HRegister::HRegister()
    : d_ptr(new HRegisterPrivate(this))
{
}

HRegister::HRegister(HRegisterPrivate &dd)
    : d_ptr(&dd)
{
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
    Q_D(HRegister);
    try
    {
        auto reg = std::make_shared<QSettings>(REGISTRY_KEY, QSettings::NativeFormat);
        reg->setValue(REGISTER_CODE, registerCode);
        reg->setValue(REGISTER_ID, d->_registerId);
        reg->setValue(SERIAL_NUMBER, d->_serialNumber);
        return true;
    }
    catch (exception e)
    {
        return false;
    }
}

QString HRegister::getRegisterId()
{
    Q_D(HRegister);
    if (!d->_registerId.isEmpty())
        return d->_registerId;

    DWORD volumeSerialNumber;
    GetVolumeInformation(L"C:\\", nullptr, 0, &volumeSerialNumber, nullptr, nullptr, nullptr, 0);
    d->_serialNumber =  QString::number(volumeSerialNumber, 16).toUpper();
    QString zcmNumber = "";
    bool ok;
    for (int i = 0; i < d->_serialNumber.length(); i++)
        zcmNumber += QString::number(QString(d->_serialNumber[i]).toInt(&ok, 16), 10);
    d->_registerId = zcmNumber;
    return d->_registerId;
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
    Q_D(HRegister);
    auto reg = make_shared<QSettings>(REGISTRY_KEY, QSettings::NativeFormat);
    d->_trialTimes = reg->value(TRIAL_TIMES, 0).toInt();
    d->_firstDate = reg->value(FIRST_DATE, 0).toInt();
    if (d->_trialTimes == 0 && d->_firstDate == 0)
        return false;

    auto expires = encryptDate(QDate::currentDate());
    return d->_trialTimes > 60 && expires - d->_firstDate > 30;
}

void HRegister::trial()
{
    Q_D(HRegister);
    d->_trialTimes++;
    auto reg = std::make_shared<QSettings>(REGISTRY_KEY, QSettings::NativeFormat);
    reg->setValue(TRIAL_TIMES, d->_trialTimes);
    if (d->_firstDate == 0)
        reg->setValue(FIRST_DATE, encryptDate(QDate::currentDate()));
}
