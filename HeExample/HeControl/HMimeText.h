/***************************************************************************************************
**      2019-12-26  HMimeText
***************************************************************************************************/

#ifndef HMIMETEXT_H
#define HMIMETEXT_H

#include "HMimePart.h"

HE_CONTROL_BEGIN_NAMESPACE

class HMimeTextPrivate;

class HMimeText : public HMimePart
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HMimeText)

public:
    explicit HMimeText(QString text = QString(), QObject *parent = nullptr);
    ~HMimeText() override;

public:
    QString text() const;

public:
    void setText(const QString &value);

public:
    void prepare() override;

protected:
    HMimeText(HMimeTextPrivate &p, QString text = QString(), QObject *parent = nullptr);
};

HE_CONTROL_END_NAMESPACE

#endif // HMIMETEXT_H
