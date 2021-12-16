/***************************************************************************************************
**      2019-12-26  HMimeText
***************************************************************************************************/

#pragma once

#include "HMimePart.h"

HE_BEGIN_NAMESPACE

class HMimeTextPrivate;

class HMimeText : public HMimePart
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HMimeText)

public:
    explicit HMimeText(const QString &text = QString(), QObject *parent = nullptr);

public:
    QString text() const;

public:
    void setText(const QString &);

public:
    void prepare() override;

protected:
    HMimeText(HMimeTextPrivate &p, const QString &text = QString(), QObject *parent = nullptr);
};

HE_END_NAMESPACE
