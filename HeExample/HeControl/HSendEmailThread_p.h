#pragma once

#include "HSendEmailThread.h"

class QMutex;

HE_CONTROL_BEGIN_NAMESPACE

class HSendEmailThreadPrivate
{
public:
    HSendEmailThreadPrivate();

public:
    QString sender;         // 发件人邮箱
    QString senderPwd;      // 发件人密码
    QString recipientTo;    // 收件人邮箱,可多个中间;隔开
    QString recipientCc;    // 抄送
    QString recipientBcc;   // 密抄
    QString title;          // 邮件标题
    QStringList contents;   // 正文内容
    QStringList fileNames;  // 附件

    QMutex *mutex;
    volatile bool stopped = false;
};

HE_CONTROL_END_NAMESPACE
