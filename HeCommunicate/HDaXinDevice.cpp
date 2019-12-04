#include "HDaXinDevice_p.h"
#include "HSerialPort.h"
#include <QtCore/QDebug>

HE_COMMUNICATE_BEGIN_NAMESPACE

const uint crc_tab[] = { 0x0000, 0x1021, 0x2042, 0x3063,
                         0x4084, 0x50a5, 0x60c6, 0x70e7,
                         0x8108, 0x9129, 0xa14a, 0xb16b,
                         0xc18c, 0xd1ad, 0xe1ce, 0xf1ef };

uint getCrc16(uchar *data, uchar size)
{
    uint crc = 0;
    char da;
    while (size-- != 0)
    {
        da = (static_cast<uchar>(crc / 256)) / 16;
        crc <<= 4;
        crc ^= crc_tab[da ^(*data / 16)];
        da = (static_cast<uchar>(crc / 256)) / 16;
        crc <<= 4;
        crc ^= crc_tab[da ^(*data & 0x0F)];
        data++;
    }
    return(crc);
}

HDaXinDevicePrivate::HDaXinDevicePrivate()
{
    QVariantMap param;
    param.insert("timeOut", 1000);
    param.insert("baudRate", 38400);
    port = new HSerialPort();
    port->initialize(param);
    actionParams.insert(ACT_SET_OUTPUT_VOLTAGE,     QList<uchar>() << 0x00 << 0x02 << 0x20);
    actionParams.insert(ACT_SET_OUTPUT_CURRENT,     QList<uchar>() << 0x00 << 0x02 << 0x21);
    actionParams.insert(ACT_SET_OVER_VOLTAGE,       QList<uchar>() << 0x00 << 0x02 << 0x22);
    actionParams.insert(ACT_SET_OVER_CURRENT,       QList<uchar>() << 0x00 << 0x02 << 0x23);
    actionParams.insert(ACT_SET_SOURCE_MODE,        QList<uchar>() << 0x00 << 0x02 << 0x24);
    actionParams.insert(ACT_SET_SOURCE_ADDR,        QList<uchar>() << 0x00 << 0x02 << 0x25);
    actionParams.insert(ACT_SET_SOURCE_OPERATION,   QList<uchar>() << 0x00 << 0x02 << 0x26);
    actionParams.insert(ACT_SET_SOURCE_FORWARD,     QList<uchar>() << 0x00 << 0x02 << 0x30);
    actionParams.insert(ACT_SET_SOURCE_REVERSE,     QList<uchar>() << 0x00 << 0x02 << 0x31);
    actionParams.insert(ACT_SET_SOURCE_IO,          QList<uchar>() << 0x00 << 0x02 << 0x32);
    actionParams.insert(ACT_GET_SOURCE_STATE,       QList<uchar>() << 0x00 << 0x01 << 0x27);
    actionParams.insert(ACT_GET_ELEC_PARAM,         QList<uchar>() << 0x00 << 0x05 << 0x28);
    da = 0x00;
    sa = 0xFB;
}

HDaXinDevice::HDaXinDevice() :
    HAbstractDevice(*new HDaXinDevicePrivate)
{
}

HDaXinDevice::~HDaXinDevice()
{
    qDebug() << __func__;
}

QString HDaXinDevice::typeName()
{
    return "HDaXinDevice";
}

HErrorType HDaXinDevice::setData(HActionType action, QVector<uchar> value, int delay)
{
    Q_D(HDaXinDevice);
    auto param = d->actionParams.value(action);
    if (param.size() < 3)
        return E_DEVICE_ACTION_PARAM_ERROR;

    auto size = value.size();
    auto upData = QVector<uchar>(10);
    auto downData = QVector<uchar>() << d->da << d->sa << param[2] << 0x80 << size % 256 << value;
    if (size == 0)
        downData << 0x00;
    auto crc = getCrc16(downData.data(), downData.size());
    downData.prepend(0x5A);
    downData.prepend(0xA5);
    downData << crc / 256 << crc % 256;

    auto error = transport(downData, upData, delay);
    if (error != E_OK)
        return error;

    if (upData.size() < 10
            || upData[0] != 0xA5
            || upData[1] != 0x5A
            || upData[2] != d->sa
            || upData[3] != d->da
            || upData[4] != param[2]
            || upData[5] != 00
            || upData[6] != 01
            || upData[7] != 00)
        return E_DEVICE_DATA_RETURN_ERROR;
    return E_OK;
}

HErrorType HDaXinDevice::getData(HActionType action, QVector<uchar> &value, int delay)
{
    Q_D(HDaXinDevice);
    auto param = d->actionParams.value(action);
    if (param.size() < 3)
        return E_DEVICE_ACTION_PARAM_ERROR;

    auto upData = QVector<uchar>(9 + param[0] * 256 + param[1]);
    auto downData =  QVector<uchar>() << d->da << d->sa << param[2] << 0x80 << 0x00;
    auto crc = getCrc16(downData.data(), downData.size());
    downData.prepend(0x5A);
    downData.prepend(0xA5);
    downData << crc / 256 << crc % 256;

    auto error = transport(downData, upData, delay);
    if (error != E_OK)
        return error;
    if (upData.size() < 10
            || upData[0] != 0xA5
            || upData[1] != 0x5A
            || upData[2] != d->sa
            || upData[3] != d->da
            || upData[4] != param[2]
            || upData[5] != 00)
        return E_DEVICE_DATA_RETURN_ERROR;
    upData.removeLast();
    upData.removeLast();
    value = upData.mid(7);
    return E_OK;
}

HErrorType HDaXinDevice::check()
{
    auto error = setData(ACT_SET_SOURCE_OPERATION, QVector<uchar>() << 0x00);
    if (error != E_OK)
        return error;
    return setData(ACT_SET_OUTPUT_CURRENT, QVector<uchar>() << 0x00 << 0x00);
}

HErrorType HDaXinDevice::transport(QVector<uchar> &downData, QVector<uchar> &upData, int delay)
{
    Q_D(HDaXinDevice);
    return d->port->transport(downData, upData, delay);
}

HE_COMMUNICATE_END_NAMESPACE
