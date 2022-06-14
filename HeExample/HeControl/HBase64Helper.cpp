#include "HBase64Helper.h"
#include <QtCore/QBuffer>
#include <QtGui/QImage>

HE_BEGIN_NAMESPACE

// 这个转换可能比较耗时建议在线程中执行
QByteArray He::HBase64Helper::toBase64(const QImage &image)
{
    QByteArray data;
    QBuffer buffer(&data);
    image.save(&buffer, "JPG");
    return data.toBase64();
}

QString HBase64Helper::toBase64s(const QImage &image)
{
    return QString(toBase64(image));
}
// 这个转换可能比较耗时建议在线程中执行
QImage HBase64Helper::toImage(const QByteArray &data)
{
    QImage image;
    image.loadFromData(QByteArray::fromBase64(data));
    return image;
}

QImage HBase64Helper::toImage(const QString &data)
{
    return toImage(data.toUtf8());
}

QByteArray HBase64Helper::toBase64(const QString &text)
{
    return text.toUtf8().toBase64();
}

QString HBase64Helper::toBase64s(const QString &text)
{
    return QString(toBase64(text));
}

QString HBase64Helper::toText(const QByteArray &data)
{
    return QString(QByteArray::fromBase64(data));
}

QString HBase64Helper::toText(const QString &data)
{
    return toText(data.toUtf8());
}

HE_END_NAMESPACE
