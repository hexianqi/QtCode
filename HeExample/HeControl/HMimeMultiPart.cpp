#include "HMimeMultiPart_p.h"
#include <QtCore/QCryptographicHash>

HE_BEGIN_NAMESPACE

QString MULTI_PART_NAMES[] =
{
    "multipart/mixed",         //    Mixed
    "multipart/digest",        //    Digest
    "multipart/alternative",   //    Alternative
    "multipart/related",       //    Related
    "multipart/report",        //    Report
    "multipart/signed",        //    Signed
    "multipart/encrypted"      //    Encrypted
};

HMimeMultiPartPrivate::HMimeMultiPartPrivate()
{
    mimeType = HMimeMultiPart::Related;
    contentType = MULTI_PART_NAMES->at(mimeType);
    contentEncoding = HMimePart::_8Bit;
    QCryptographicHash md5(QCryptographicHash::Md5);
    md5.addData(QByteArray().append(static_cast<char>(qrand())));
    contentBoundary = md5.result().toHex();
}

HMimeMultiPart::HMimeMultiPart(QObject *parent) :
    HMimePart(*new HMimeMultiPartPrivate, parent)
{
}

HMimeMultiPart::HMimeMultiPart(HMimeMultiPartPrivate &p, QObject *parent) :
    HMimePart(p, parent)
{
}

HMimeMultiPart::MimeType HMimeMultiPart::mimeType() const
{
    Q_D(const HMimeMultiPart);
    return d->mimeType;
}

QList<HMimePart *> HMimeMultiPart::parts() const
{
    Q_D(const HMimeMultiPart);
    return d->parts;
}

void HMimeMultiPart::setMimeType(MimeType type)
{
    Q_D(HMimeMultiPart);
    d->mimeType = type;
    d->contentType = MULTI_PART_NAMES->at(type);
}

void HMimeMultiPart::addPart(HMimePart *p)
{
    Q_D(HMimeMultiPart);
    d->parts.append(p);
}

void HMimeMultiPart::prepare()
{
    Q_D(HMimeMultiPart);
    QStringList list;
    auto sep = QString("--%1\r\n").arg(d_ptr->contentBoundary);
    for (auto p : d->parts)
    {
        p->prepare();
        list << p->toString();
    }
    d->content = QString("%1%2--%3--\r\n").arg(sep, list.join(sep), d_ptr->contentBoundary).toUtf8();
    HMimePart::prepare();
}

HE_END_NAMESPACE
