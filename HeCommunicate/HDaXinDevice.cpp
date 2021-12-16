#include "HDaXinDevice_p.h"
#include "IPort.h"
#include "HeCore/HException.h"
#include <QtCore/QVector>

HE_BEGIN_NAMESPACE

uint crc_tab[] = { 0x0000, 0x1021, 0x2042, 0x3063,
                   0x4084, 0x50a5, 0x60c6, 0x70e7,
                   0x8108, 0x9129, 0xa14a, 0xb16b,
                   0xc18c, 0xd1ad, 0xe1ce, 0xf1ef };

uint getCrc16(uchar *data, uchar size)
{
    uint crc = 0;
    char da;
    while (size-- != 0)
    {
        da = (uchar(crc / 256)) / 16;
        crc <<= 4;
        crc ^= crc_tab[da ^(*data / 16)];
        da = (uchar(crc / 256)) / 16;
        crc <<= 4;
        crc ^= crc_tab[da ^(*data & 0x0F)];
        data++;
    }
    return crc;
}

//quint16 crc16(const QVector<uchar> &data)
//{
//    quint16 c;
//    quint16 crc16 = 0xFFFF;
//    for (auto i : data)
//    {
//        c = i & 0x00FF;
//        crc16 ^= c;
//        for (int j = 0; j < 8; j++)
//        {
//            if(crc16 & 0x0001)
//            {
//                crc16 >>= 1;
//                crc16 ^= 0xA001;
//            }
//            else
//            {
//                crc16 >>= 1;
//            }
//        }
//    }
//    crc16 = (crc16 >> 8) + (crc16 << 8);
//    return crc16;
//}

HDaXinDevicePrivate::HDaXinDevicePrivate()
{
    da = 0x00;
    sa = 0xFB;
}

HDaXinDevice::HDaXinDevice() :
    HAbstractDevice(*new HDaXinDevicePrivate)
{
}

HDaXinDevice::~HDaXinDevice() = default;

QString HDaXinDevice::typeName()
{
    return "HDaXinDevice";
}

bool HDaXinDevice::setData(HActionType action, QVector<uchar> value, int delay)
{
    Q_D(HDaXinDevice);
    auto param = d->actionParams.value(action);
    if (param.size() < 3)
        throw HException(E_DEVICE_ACTION_PARAM_ERROR);

    auto size = value.size();
    auto upData = QVector<uchar>(10);
    auto downData = QVector<uchar>() << d->da << d->sa << param[2] << 0x80 << uchar(size % 256) << value;
    if (size == 0)
        downData << 0x00;
    auto crc = getCrc16(downData.data(), downData.size());
    downData.prepend(0x5A);
    downData.prepend(0xA5);
    downData << uchar(crc / 256) << uchar(crc % 256);

    transport(downData, upData, delay);

    if (upData.size() < 10
            || upData[0] != 0xA5
            || upData[1] != 0x5A
            || upData[2] != d->sa
            || upData[3] != d->da
            || upData[4] != param[2]
            || upData[5] != 00
            || upData[6] != 01
            || upData[7] != 00)
        throw HException(E_DEVICE_DATA_RETURN_ERROR);
    return true;
}

bool HDaXinDevice::getData(HActionType action, QVector<uchar> &value, int delay)
{
    Q_D(HDaXinDevice);
    auto param = d->actionParams.value(action);
    if (param.size() < 3)
        throw HException(E_DEVICE_ACTION_PARAM_ERROR);

    auto size = param[0] * 256 + param[1];
    auto upData = QVector<uchar>(9 + size);
    auto downData =  QVector<uchar>() << d->da << d->sa << param[2] << 0x80 << 0x00;
    auto crc = getCrc16(downData.data(), downData.size());
    downData.prepend(0x5A);
    downData.prepend(0xA5);
    downData << uchar(crc / 256) << uchar(crc % 256);

    transport(downData, upData, delay);

    if (upData.size() < 10
            || upData[0] != 0xA5
            || upData[1] != 0x5A
            || upData[2] != d->sa
            || upData[3] != d->da
            || upData[4] != param[2]
            || upData[5] != 00)
        throw HException(E_DEVICE_DATA_RETURN_ERROR);
    value = upData.mid(7, size);
    return true;
}

bool HDaXinDevice::check()
{
    return setData(ACT_SET_SOURCE_OPERATION, QVector<uchar>() << 0x00) &&
           setData(ACT_SET_OUTPUT_CURRENT, QVector<uchar>() << 0x00 << 0x00);
}

HE_END_NAMESPACE
