/***************************************************************************************************
**      2019-12-26  HMimeHtml
***************************************************************************************************/

#pragma once

#include "HMimeText.h"

HE_BEGIN_NAMESPACE

class HMimeHtmlPrivate;

class HMimeHtml : public HMimeText
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HMimeHtml)

public:
    explicit HMimeHtml(const QString &html = QString(), QObject *parent = nullptr);

public:
    QString html() const;

public:
    void setHtml(const QString &);

protected:
    HMimeHtml(HMimeHtmlPrivate &p, const QString &html = QString(), QObject *parent = nullptr);
};

HE_END_NAMESPACE
