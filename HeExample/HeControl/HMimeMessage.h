/***************************************************************************************************
**      2019-12-25  HMimeMessage
***************************************************************************************************/

#pragma once

#include "HMimePart.h"

HE_CONTROL_BEGIN_NAMESPACE

class HEmailAddress;
class HMimeMessagePrivate;

class HMimeMessage : public QObject
{
    Q_OBJECT

public:
    enum RecipientType
    {
        To,                 // primary
        Cc,                 // carbon copy
        Bcc                 // blind carbon copy
    };

public:
    explicit HMimeMessage(QObject *parent = nullptr);
    ~HMimeMessage() override;

public:
    HEmailAddress *sender();
    HEmailAddress *replyTo() const;
    QList<HEmailAddress *> recipients() const;
    QList<HEmailAddress *> recipients(RecipientType type) const;
    QString subject() const;
    HMimePart *content();
    QList<HMimePart *> parts() const;

public:
    void setSender(HEmailAddress *);
    void setReplyTo(HEmailAddress *);
    void addRecipient(HEmailAddress *, RecipientType type = To);
    void addRecipientTo(HEmailAddress *);
    void addRecipientCc(HEmailAddress *);
    void addRecipientBcc(HEmailAddress *);
    void setSubject(const QString &value);
    void setContent(HMimePart *);
    void addPart(HMimePart *);
    void setInReplyTo(const QString &value);
    void setHeaderEncoding(HMimePart::Encoding value);

public:
    virtual QString toString();

protected:
    QString encode(const QString &value);
    QString toString(HEmailAddress *);
    QString toString(QList<HEmailAddress *>);

protected:
    QScopedPointer<HMimeMessagePrivate> d_ptr;
};

HE_CONTROL_END_NAMESPACE
