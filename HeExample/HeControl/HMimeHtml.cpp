#include "HMimeHtml_p.h"

HE_CONTROL_BEGIN_NAMESPACE

HMimeHtmlPrivate::HMimeHtmlPrivate()
{
    contentType = "text/html";
}

HMimeHtml::HMimeHtml(const QString &html, QObject *parent) :
    HMimeText(*new HMimeHtmlPrivate, html, parent)
{
}

HMimeHtml::HMimeHtml(HMimeHtmlPrivate &p, const QString &html, QObject *parent) :
    HMimeText(p, html, parent)
{
}

QString HMimeHtml::html() const
{
    return text();
}

void HMimeHtml::setHtml(const QString &value)
{
    setText(value);
}

HE_CONTROL_END_NAMESPACE
