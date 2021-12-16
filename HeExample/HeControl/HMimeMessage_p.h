#pragma once

#include "HMimeMessage.h"
#include <QtCore/QList>

HE_BEGIN_NAMESPACE

class HMimeMessagePrivate
{
public:
    HEmailAddress *sender = nullptr;
    HEmailAddress *replyTo = nullptr;
    QList<HEmailAddress *> recipientsTo;
    QList<HEmailAddress *> recipientsCc;
    QList<HEmailAddress *> recipientsBcc;
    HMimePart::Encoding encoding;
    QString subject;
    QString inReplyTo;
    HMimePart *content = nullptr;
};

HE_END_NAMESPACE
