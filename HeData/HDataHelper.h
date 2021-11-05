/***************************************************************************************************
**      2019-05-22  HDataHelper 数据帮助类。
***************************************************************************************************/

#pragma once

#include "HDataGlobal.h"
#include <QtCore/QVariant>

HE_DATA_BEGIN_NAMESPACE

class HE_DATA_EXPORT HDataHelper
{
public:
    static quint16 readUInt16(QVector<uchar> data, int &pos);
    static QVector<uchar> writeUInt16(quint16 data);
    static bool checkHead(const QVector<uchar> &data, int &pos, int &version);

public:
    // 增补
    static QSet<QString> supplement(QSet<QString> set, QSet<QString> other);
    // 衍生
    static QVariant derive(QString type, QVariantMap data);
};

HE_DATA_END_NAMESPACE
