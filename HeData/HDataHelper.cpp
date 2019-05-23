#include "HDataHelper.h"
#include <QtCore/QVector>

HE_DATA_BEGIN_NAMESPACE

quint16 HDataHelper::readUInt16(QVector<uchar> data, int &pos)
{
    auto v1 = data[pos++];
    auto v2 = data[pos++];
    return v1 * 256 + v2;
}

QVector<uchar> HDataHelper::writeUInt16(quint16 data)
{
    return QVector<uchar>() << data / 256 << data % 256;
}

bool HDataHelper::checkHead(QVector<uchar> data, int &pos, int &version)
{
    if (data.size() < pos + 4)
        return false;
    int size = readUInt16(data, pos);
    version = readUInt16(data, pos);
    return data.size() >= size + pos - 4;
}

HE_DATA_END_NAMESPACE
