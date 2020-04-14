#include "HMimeText_p.h"

HE_CONTROL_BEGIN_NAMESPACE

HMimeTextPrivate::HMimeTextPrivate()
{
    contentType = "text/plain";
    contentCharset = "utf-8";
    contentEncoding = HMimePart::_8Bit;
}

HMimeText::HMimeText(const QString &text, QObject *parent) :
    HMimePart(*new HMimeTextPrivate, parent)
{
    setText(text);
}

HMimeText::HMimeText(HMimeTextPrivate &p, const QString &text, QObject *parent) :
    HMimePart(p, parent)
{
    setText(text);
}

QString HMimeText::text() const
{
    Q_D(const HMimeText);
    return d->text;
}

void HMimeText::setText(const QString &value)
{
    Q_D(HMimeText);
    if (d->text == value)
        return;
    d->text = value;
}

void HMimeText::prepare()
{
    Q_D(HMimeText);
    d->content = d->text.toUtf8();
    HMimePart::prepare();
}

HE_CONTROL_END_NAMESPACE
