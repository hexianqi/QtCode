/***************************************************************************************************
**      2019-12-26  HSendEmailThread
***************************************************************************************************/

#pragma once

#include "HControlGlobal.h"
#include <QtCore/QThread>

HE_CONTROL_BEGIN_NAMESPACE

class HSendEmailThreadPrivate;

class HSendEmailThread : public QThread
{
    Q_OBJECT

public:
    explicit HSendEmailThread(QObject *parent = nullptr);
    ~HSendEmailThread() override;

signals:
    void receiveEmailResult(const QString &value);

public slots:
    void setSender(const QString &value);
    void setSenderPwd(const QString &value);
    void setRecipientTo(const QString &value);
    void setRecipientCc(const QString &value);
    void setRecipientBcc(const QString &value);
    void send(const QString &title, const QString &content, const QString &fileName);
    void stop();

protected:
    HSendEmailThread(HSendEmailThreadPrivate &p, QObject *parent = nullptr);

protected:
    void run() override;
    bool dequeue(QString &content, QString &fileName);

protected:
    QScopedPointer<HSendEmailThreadPrivate> d_ptr;
};

HE_CONTROL_END_NAMESPACE
