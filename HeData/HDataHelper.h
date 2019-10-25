/***************************************************************************************************
**      2019-05-22  HDataHelper 数据帮助类。
***************************************************************************************************/

#ifndef HDATAHELPER_H
#define HDATAHELPER_H

#include "HDataGlobal.h"

HE_DATA_BEGIN_NAMESPACE

class HDataHelper
{
public:
    static quint16 readUInt16(QVector<uchar> data, int &pos);
    static QVector<uchar> writeUInt16(quint16 data);
    static bool checkHead(QVector<uchar> data, int &pos, int &version);
};

HE_DATA_END_NAMESPACE

#endif // HDATAHELPER_H
