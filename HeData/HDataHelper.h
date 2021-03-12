/***************************************************************************************************
**      2019-05-22  HDataHelper 数据帮助类。
***************************************************************************************************/

#pragma once

#include "HDataGlobal.h"

HE_DATA_BEGIN_NAMESPACE

class HDataHelper
{
public:
    static quint16 readUInt16(QVector<uchar> data, int &pos);
    static QVector<uchar> writeUInt16(quint16 data);
    static bool checkHead(const QVector<uchar> &data, int &pos, int &version);
};

HE_DATA_END_NAMESPACE
