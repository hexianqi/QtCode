/***************************************************************************************************
**      2019-05-22  HDataHelper 数据帮助类。
***************************************************************************************************/

#pragma once

#include "HNamespace.h"
#include <QtCore/QVariant>

HE_BEGIN_NAMESPACE

class HDataHelper
{
public:
    static quint16 readUInt16(QVector<uchar> data, int &pos);
    static double readDouble(QVector<uchar> data, int &pos);
    static QString readString(QVector<uchar> data, int &pos);
    static QVector<uchar> writeUInt16(quint16 data);
    static QVector<uchar> writeDouble(double data);
    static QVector<uchar> writeString(QString data);
    static bool checkHead(const QVector<uchar> &data, int &pos, int &version);

public:
    // 增补
    static QSet<QString> supplement(QSet<QString> set, QSet<QString> other);
    // 衍生
    static QVariant derive(QString type, QVariantMap data);
};

HE_END_NAMESPACE
