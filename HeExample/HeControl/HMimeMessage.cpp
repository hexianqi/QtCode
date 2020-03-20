#include "HMimeMessage_p.h"
#include "HEmailAddress.h"
#include "HMimeMultiPart.h"
#include "HQuotedPrintable.h"
#include <QtCore/QDateTime>

HE_CONTROL_BEGIN_NAMESPACE

HMimeMessage::HMimeMessage(QObject *parent) :
    QObject(parent),
    d_ptr(new HMimeMessagePrivate)
{
    d_ptr->content = new HMimeMultiPart(this);
}

HMimeMessage::~HMimeMessage()
{

}

HEmailAddress *HMimeMessage::sender()
{
    return d_ptr->sender;
}

HEmailAddress *HMimeMessage::replyTo() const
{
    return  d_ptr->replyTo;
}

QList<HEmailAddress *> HMimeMessage::recipients() const
{
    return QList<HEmailAddress *>() << d_ptr->recipientsTo << d_ptr->recipientsCc << d_ptr->recipientsBcc;
}

QList<HEmailAddress *> HMimeMessage::recipients(HMimeMessage::RecipientType type) const
{
    if (type == To)
        return d_ptr->recipientsTo;
    if (type == Cc)
        return d_ptr->recipientsCc;
    if (type == Bcc)
        return d_ptr->recipientsBcc;
    return recipients();
}

QString HMimeMessage::subject() const
{
    return d_ptr->subject;
}

HMimePart *HMimeMessage::content()
{
    return d_ptr->content;
}

QList<HMimePart *> HMimeMessage::parts() const
{
    auto c = qobject_cast<HMimeMultiPart *>(d_ptr->content);
    if (c != nullptr)
        return c->parts();
    return QList<HMimePart *>() << d_ptr->content;
}

void HMimeMessage::setSender(HEmailAddress *p)
{
    d_ptr->sender = p;
    d_ptr->sender->setParent(this);
}

void HMimeMessage::setReplyTo(HEmailAddress *p)
{
    d_ptr->replyTo = p;
    d_ptr->replyTo->setParent(this);
}

void HMimeMessage::addRecipient(HEmailAddress *p, HMimeMessage::RecipientType type)
{
    if (type == To)
        addRecipientTo(p);
    if (type == Cc)
        addRecipientCc(p);
    if (type == Bcc)
        addRecipientBcc(p);
}

void HMimeMessage::addRecipientTo(HEmailAddress *p)
{
    d_ptr->recipientsTo << p;
    p->setParent(this);
}

void HMimeMessage::addRecipientCc(HEmailAddress *p)
{
    d_ptr->recipientsCc << p;
    p->setParent(this);
}

void HMimeMessage::addRecipientBcc(HEmailAddress *p)
{
    d_ptr->recipientsBcc << p;
    p->setParent(this);
}

void HMimeMessage::setSubject(const QString &value)
{
    d_ptr->subject = value;
}

void HMimeMessage::setContent(HMimePart *p)
{
    d_ptr->content = p;
    d_ptr->content->setParent(this);
}

void HMimeMessage::addPart(HMimePart *p)
{
    auto c = qobject_cast<HMimeMultiPart *>(d_ptr->content);
    if (c != nullptr)
        c->addPart(p);
}

void HMimeMessage::setInReplyTo(const QString &value)
{
    d_ptr->inReplyTo = value;

}

void HMimeMessage::setHeaderEncoding(HMimePart::Encoding value)
{
    d_ptr->encoding = value;
}

QString HMimeMessage::toString()
{
    QStringList data;

    /* =========== MIME HEADER =========== */
    /* ---------- Sender / From ---------- */
    data << QString("From:%1").arg(toString(d_ptr->sender));
    /* --------- Recipients / To --------- */
    data << QString("To:%1").arg(toString(d_ptr->recipientsTo));
    /* --------- Recipients / Cc --------- */
    if (d_ptr->recipientsCc.size() > 0)
        data << QString("Cc:%1").arg(toString(d_ptr->recipientsCc));
    /* ------------- Subject ------------- */
    data << QString("Subject: %1").arg(encode(d_ptr->subject));
    /* ------------- Reply-To ------------ */
    if (d_ptr->replyTo != nullptr)
        data << QString("Reply-To:%1").arg(toString(d_ptr->replyTo));
    /* ------------- Version ------------- */
    data << QString("MIME-Version: 1.0");
    /* ----------- In-Reply-To ----------- */
    if (!d_ptr->inReplyTo.isEmpty())
        data << QString("In-Reply-To: <%1>").arg(d_ptr->inReplyTo) << QString("References: <%1>").arg(d_ptr->inReplyTo);
    /* --------------- Date -------------- */
    data << QString("Date: %1").arg(QDateTime::currentDateTime().toString(Qt::RFC2822Date));
    /* ------------- Content ------------- */
    data << d_ptr->content->toString();
    return data.join("\r\n");
}

QString HMimeMessage::encode(const QString &value)
{
    if (d_ptr->encoding == HMimePart::Base64)
        return "=?utf-8?B?" + QByteArray().append(value).toBase64() + "?=";
    if (d_ptr->encoding == HMimePart::QuotedPrintable)
        return "=?utf-8?Q?" + HQuotedPrintable::encode(QByteArray().append(value)).replace(' ', "_").replace(':',"=3A") + "?=";
    return value;
}

QString HMimeMessage::toString(HEmailAddress *p)
{
    QString name;
    if (!p->name().isEmpty())
        name = encode(p->name());
    return QString(" %1 <%2>").arg(name).arg(p->address());
}

QString HMimeMessage::toString(QList<HEmailAddress *> p)
{
    QStringList list;
    for (auto i : p)
        list << toString(i);
    return list.join(",");
}

HE_CONTROL_END_NAMESPACE
