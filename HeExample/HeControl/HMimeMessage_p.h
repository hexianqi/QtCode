#ifndef HMIMEMESSAGE_P_H
#define HMIMEMESSAGE_P_H

#include "HMimeMessage.h"
#include <QtCore/QList>

HE_CONTROL_BEGIN_NAMESPACE

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

HE_CONTROL_END_NAMESPACE

#endif // HMIMEMESSAGE_P_H
