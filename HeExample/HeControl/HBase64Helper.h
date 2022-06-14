#pragma once

#include "HNamespace.h"
#include <QtCore/qglobal.h>

class QImage;

HE_BEGIN_NAMESPACE

class HBase64Helper
{
public:
    // 图片与base64字符串互转
    static QByteArray toBase64(const QImage &);
    static QString toBase64s(const QImage &);
    static QImage toImage(const QByteArray &);
    static QImage toImage(const QString &);
    // 字符串与base64字符串互转
    static QByteArray toBase64(const QString &);
    static QString toBase64s(const QString &);
    static QString toText(const QByteArray &);
    static QString toText(const QString &);

};

HE_END_NAMESPACE

