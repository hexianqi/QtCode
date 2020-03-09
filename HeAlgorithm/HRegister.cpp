#include "HRegister_p.h"
#include <QtCore/QSettings>
#include <QtCore/QDate>
#include <QtCore/QDebug>
#include <exception>
#include <windows.h>

HE_ALGORITHM_BEGIN_NAMESPACE

using namespace std;

const QString REGISTRY_KEY = "HKEY_CURRENT_USER\\Software\\Test";
const QString REGISTER_ID = "banben";
const QString REGISTER_CODE = "xulie";
const QString SERIAL_NUMBER = "ma_no";
const QString TRIAL_TIMES = "trti";
const QString FIRST_DATE = "fida";

void splitRegisterId(QString id, int &i1, int &i2)
{
    if (id.length() < 10)
    {
        for (int i = 1; i <= 10 - id.length(); i++)
            id = id + QString::number(i);
    }
    if (id.length() > 10)
        id = id.left(10);

    i1 = id.left(5).toInt();
    i2 = id.right(5).toInt();
}

int encryptDate(QDate value)
{
    return (value.year() - 2010) * 430 + value.month() * 32 + value.day();
}

QString HRegisterPrivate::registerId()
{
    if (!id.isEmpty())
        return id;

    DWORD volumeSerialNumber;
    GetVolumeInformation(L"C:\\", nullptr, 0, &volumeSerialNumber, nullptr, nullptr, nullptr, 0);
    serialNumber =  QString::number(volumeSerialNumber, 16).toUpper();
    QString zcmNumber = "";
    bool ok;
    for (int i = 0; i < serialNumber.length(); i++)
        zcmNumber += QString::number(QString(serialNumber[i]).toInt(&ok, 16), 10);
    id = zcmNumber;
    return id;
}

QString HRegisterPrivate::registerCode()
{
    try
    {
        QSettings reg(REGISTRY_KEY, QSettings::NativeFormat);
        return reg.value(REGISTER_CODE).toString();
    }
    catch (exception e)
    {
        qDebug() << __func__ << e.what();
        return QString();
    }
}

bool HRegisterPrivate::isExpires()
{
    QSettings reg(REGISTRY_KEY, QSettings::NativeFormat);
    trialTimes = reg.value(TRIAL_TIMES, 0).toInt();
    firstDate = reg.value(FIRST_DATE, 0).toInt();
    if (trialTimes == 0 && firstDate == 0)
        return false;
    return trialTimes > 100 && encryptDate(QDate::currentDate()) - firstDate > 60;
}

void HRegisterPrivate::trial()
{
    QSettings reg(REGISTRY_KEY, QSettings::NativeFormat);
    trialTimes++;
    reg.setValue(TRIAL_TIMES, trialTimes);
    if (firstDate == 0)
        reg.setValue(FIRST_DATE, encryptDate(QDate::currentDate()));
}

bool HRegisterPrivate::setRegisterCode(const QString &value)
{
    try
    {
        QSettings reg(REGISTRY_KEY, QSettings::NativeFormat);
        reg.setValue(REGISTER_CODE, value);
        reg.setValue(REGISTER_ID, id);
        reg.setValue(SERIAL_NUMBER, serialNumber);
        return true;
    }
    catch (exception e)
    {
        qDebug() << __func__ << e.what();
        return false;
    }
}

HRegister::HRegister(QObject *parent) :
    QObject(parent),
    d_ptr(new HRegisterPrivate)
{
}

HRegister::HRegister(HRegisterPrivate &p, QObject *parent) :
    QObject(parent),
    d_ptr(&p)
{
}

HRegister::~HRegister()
{
    qDebug() << __func__;
}

QString HRegister::registerId()
{
    return d_ptr->registerId();
}

QString HRegister::registerCode()
{
    return d_ptr->registerCode();
}

bool HRegister::isExpires()
{
    return d_ptr->isExpires();
}

bool HRegister::setRegisterCode(const QString &value)
{
    return d_ptr->setRegisterCode(value);
}

bool HRegister::check()
{
    auto id = registerId();
    auto code = registerCode();
    return check(id, code);
}

bool HRegister::check(const QString &id, const QString &code)
{
    try
    {
        return encrypt(id) == code;
    }
    catch (exception e)
    {
        qDebug() << __func__ << e.what();
        return false;
    }
}

QString HRegister::encrypt(QString id)
{
    int i1, i2;
    splitRegisterId(id, i1, i2);
    id = QString::number(i1 * 5918 + i2 * 5858);
    splitRegisterId(id, i1, i2);
    return QString::number(i1 ^ i2);
}

void HRegister::trial()
{
    d_ptr->trial();
}

HE_ALGORITHM_END_NAMESPACE
