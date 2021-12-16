#include "HSendEmailThread_p.h"
#include "HSmtpClient.h"
#include "HEmailAddress.h"
#include "HMimeMessage.h"
#include "HMimeHtml.h"
#include "HMimeAttachment.h"
#include <QtCore/QFile>
#include <QtCore/QMutexLocker>
#include <QtCore/QDebug>

HE_BEGIN_NAMESPACE

HSendEmailThreadPrivate::HSendEmailThreadPrivate()
{
    mutex = new QMutex;
}

HSendEmailThread::HSendEmailThread(QObject *parent) :
    QThread(parent),
    d_ptr(new HSendEmailThreadPrivate)
{
}

HSendEmailThread::HSendEmailThread(HSendEmailThreadPrivate &p, QObject *parent) :
    QThread(parent),
    d_ptr(&p)
{
}

HSendEmailThread::~HSendEmailThread()
{
    stop();
    wait(1000);
}

void HSendEmailThread::setSender(const QString &value)
{
    if (d_ptr->sender == value)
        return;
    d_ptr->sender = value;
}

void HSendEmailThread::setSenderPwd(const QString &value)
{
    if (d_ptr->senderPwd == value)
        return;
    d_ptr->senderPwd = value;
}

void HSendEmailThread::setRecipientTo(const QString &value)
{
    if (d_ptr->recipientTo == value)
        return;
    d_ptr->recipientTo = value;
}

void HSendEmailThread::setRecipientCc(const QString &value)
{
    if (d_ptr->recipientCc == value)
        return;
    d_ptr->recipientCc = value;
}

void HSendEmailThread::setRecipientBcc(const QString &value)
{
    if (d_ptr->recipientBcc == value)
        return;
    d_ptr->recipientBcc = value;
}

void HSendEmailThread::send(const QString &title, const QString &content, const QString &fileName)
{
    QMutexLocker locker(d_ptr->mutex);
    d_ptr->title = title;
    d_ptr->contents << content;
    d_ptr->fileNames << fileName;
}

void HSendEmailThread::stop()
{
    d_ptr->stopped = true;
}

void HSendEmailThread::run()
{
    QString content, fileName, smtp, result;
    while (!d_ptr->stopped)
    {
        if (!dequeue(content, fileName))
        {
            msleep(100);
            continue;
        }
        // 构建邮件主题
        HMimeMessage message;
        // 添加发件人
        message.setSender(HEmailAddress::fromString(d_ptr->sender));
        // 添加收件人
        for (const auto &addr : d_ptr->recipientTo.split(';'))
            message.addRecipientTo(HEmailAddress::fromString(addr));
        // 添加抄送
        if (!d_ptr->recipientCc.isEmpty())
        {
            for (const auto &addr : d_ptr->recipientCc.split(';'))
                message.addRecipientCc(HEmailAddress::fromString(addr));
        }
        // 添加密抄
        if (!d_ptr->recipientBcc.isEmpty())
        {
            for (const auto &addr : d_ptr->recipientBcc.split(';'))
                message.addRecipientBcc(HEmailAddress::fromString(addr));
        }
        // 构建邮件标题
        message.setSubject(d_ptr->title);
        // 构建邮件正文
        message.addPart(new HMimeHtml(content));
        // 构建附件
        if (!fileName.isEmpty())
        {
            for (const auto &name : fileName.split(";"))
            {
                if (QFile::exists(name))
                    message.addPart(new HMimeAttachment(name));
            }
        }

        qDebug() << message.toString();

        // QQ邮箱端口号为465，必须启用SSL协议.
        smtp = d_ptr->sender.split("@").at(1).split(".").at(0).toLower();
        HSmtpClient client(QString("smtp.%1.com").arg(smtp), smtp == "qq" ? 465 : 25, smtp == "qq" ? HSmtpClient::Ssl : HSmtpClient::Tcp);
        client.setUser(d_ptr->sender);
        client.setPassword(d_ptr->senderPwd);
        if (!client.connectToHost())
        {
            result = tr("邮件服务器连接失败！");
        }
        else
        {
            if (!client.login())
                result = tr("邮件用户登录失败！");
            else
                result = client.sendMail(&message) ? tr("邮件发送成功！") : tr("邮件发送失败！");
            client.quit();
        }
        emit receiveEmailResult(result);
        msleep(1000);
    }
    d_ptr->stopped = false;
}

bool HSendEmailThread::dequeue(QString &content, QString &fileName)
{
    if (d_ptr->contents.isEmpty())
        return false;
    QMutexLocker locker(d_ptr->mutex);
    content = d_ptr->contents.takeFirst();
    fileName = d_ptr->fileNames.takeFirst();
    return true;
}

HE_END_NAMESPACE
