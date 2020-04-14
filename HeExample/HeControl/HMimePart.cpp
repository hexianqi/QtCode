#include "HMimePart_p.h"
#include "HQuotedPrintable.h"

HE_CONTROL_BEGIN_NAMESPACE

HMimePart::HMimePart(QObject *parent) :
    QObject(parent),
    d_ptr(new HMimePartPrivate)
{
}

HMimePart::HMimePart(HMimePartPrivate &p, QObject *parent) :
    QObject(parent),
    d_ptr(&p)
{
}

HMimePart::~HMimePart() = default;

QString HMimePart::header() const
{
    return d_ptr->header;
}

QByteArray HMimePart::content() const
{
    return d_ptr->content;
}

QString HMimePart::contentId() const
{
    return d_ptr->contentId;
}

QString HMimePart::contentName() const
{
    return d_ptr->contentName;
}

QString HMimePart::contentType() const
{
    return d_ptr->contentType;
}

QString HMimePart::contentCharset() const
{
    return d_ptr->contentCharset;
}

HMimePart::Encoding HMimePart::contentEncoding() const
{
    return d_ptr->contentEncoding;
}

void HMimePart::setHeader(const QString &value)
{
    if (d_ptr->header == value)
        return;
    d_ptr->header = value;
}

void HMimePart::addHeaderLine(const QString &value)
{
    d_ptr->header += value + "\r\n";
}

void HMimePart::setContent(const QByteArray &value)
{
    if (d_ptr->content == value)
        return;
    d_ptr->content = value;
}

void HMimePart::setContentId(const QString &value)
{
    if (d_ptr->contentId == value)
        return;
    d_ptr->contentId = value;
}

void HMimePart::setContentName(const QString &value)
{
    if (d_ptr->contentName == value)
        return;
    d_ptr->contentName = value;
}

void HMimePart::setContentType(const QString &value)
{
    if (d_ptr->contentType == value)
        return;
    d_ptr->contentType = value;
}

void HMimePart::setContentCharset(const QString &value)
{
    if (d_ptr->contentCharset == value)
        return;
    d_ptr->contentCharset = value;
}

void HMimePart::setContentEncoding(HMimePart::Encoding value)
{
    if (d_ptr->contentEncoding == value)
        return;
    d_ptr->contentEncoding = value;
}

QString HMimePart::toString()
{
    if (!d_ptr->prepared)
        prepare();
    return d_ptr->data;
}

void HMimePart::prepare()
{
    QStringList data;
    /* ======== Header Prepare ======== */
    /* --------- Content-Type --------- */
    auto types = QStringList() << QString("Content-Type: %1").arg(d_ptr->contentType);
    if (!d_ptr->contentName.isEmpty())
        types << QString("name=\"%1\"").arg(d_ptr->contentName);
    if (!d_ptr->contentCharset.isEmpty())
        types << QString("charset=%1").arg(d_ptr->contentCharset);
    if (!d_ptr->contentBoundary.isEmpty())
        types << QString("boundary=%1").arg(d_ptr->contentBoundary);
    data << types.join("; ");
    /* --- Content-Transfer-Encoding -- */
    auto encoding = QString("Content-Transfer-Encoding: ");
    if (d_ptr->contentEncoding == _7Bit)
        encoding += QString("7bit");
    if (d_ptr->contentEncoding == _8Bit)
        encoding += QString("8bit");
    if (d_ptr->contentEncoding == Base64)
        encoding += QString("base64");
    if (d_ptr->contentEncoding == QuotedPrintable)
        encoding += QString("quoted-printable");
    data << encoding;
    /* ---------- Content-Id ---------- */
    if (!d_ptr->contentId.isEmpty())
        data << QString("Content-ID: <%1>").arg(d_ptr->contentId);
    /* ----- Addition header lines ---- */
    data << d_ptr->header;
    /* =========== Content ============ */
    if (d_ptr->contentEncoding == _7Bit)
        data << QString(d_ptr->content).toLatin1();
    if (d_ptr->contentEncoding == _8Bit)
        data << d_ptr->content;
    if (d_ptr->contentEncoding == Base64)
        data << format(d_ptr->content.toBase64());
    if (d_ptr->contentEncoding == QuotedPrintable)
        data << format(HQuotedPrintable::encode(d_ptr->content), true);

    d_ptr->data = data.join("\r\n") + QString("\r\n");
    d_ptr->prepared = true;
}

QString HMimePart::format(const QString &content, bool quotedPrintable, int maxLength)
{
    QString result;
    int chars = 0;
    for (auto i : content)
    {
        chars++;
        if (!quotedPrintable)
        {
            if (chars > maxLength)
            {
                result.append("\r\n");
                chars = 1;
            }
        }
        else
        {
            if (i == '\n') // new line
            {
                result.append(i);
                chars = 0;
                continue;
            }
            if ((chars > maxLength - 1) || ((i == '=') && (chars > maxLength - 3)))
            {
                result.append('=');
                result.append("\r\n");
                chars = 1;
            }
        }
        result.append(i);
    }
    return result;
}

HE_CONTROL_END_NAMESPACE
