/***************************************************************************************************
**      2019-12-23  HSmtpClient SMTP客户端。
***************************************************************************************************/

#ifndef HSMTPCLIENT_H
#define HSMTPCLIENT_H

#include "HControlGlobal.h"
#include <QtCore/QObject>

HE_CONTROL_BEGIN_NAMESPACE

class HMimeMessage;
class HSmtpClientPrivate;

class HSmtpClient : public QObject
{
    Q_OBJECT

public:
    enum AuthMethod
    {
        AuthPlain,
        AuthLogin
    };

    enum SmtpError
    {
        ConnectionTimeout,
        ResponseTimeout,
        SendTimeout,
        AuthenticationFailed,
        ServerError,            // 4xx smtp error
        ClientError             // 5xx smtp error
    };

    enum ConnectionType
    {
        Tcp,
        Ssl,
        Tls       // STARTTLS
    };

public:
    explicit HSmtpClient(const QString &host = "locahost", quint16 port = 25, ConnectionType type = Tcp, QObject *parent = nullptr);
    ~HSmtpClient() override;

signals:
    void error(SmtpError value);

public:
    QString host() const;
    quint16 port() const;
    ConnectionType connectionType() const;
    AuthMethod authMethod() const;
    int connectionTimeout() const;
    int responseTimeout() const;
    int sendTimeout() const;
    QString name() const;
    QString user() const;
    QString password() const;
    QString responseText() const;
    int responseCode() const;

public:
    void setHost(const QString &value);
    void setPort(quint16 value);
    void setConnectionType(ConnectionType value);
    void setAuthMethod(AuthMethod value);
    void setConnectionTimeout(int msec);
    void setResponseTimeout(int msec);
    void setSendTimeout(int msec);
    void setName(const QString &value);
    void setUser(const QString &value);
    void setPassword(const QString &value);

public:
    bool connectToHost();
    bool login();
    bool login(const QString &user, const QString &password, AuthMethod method = AuthLogin);
    bool sendMail(HMimeMessage *value);
    void quit();

protected:
    void close();
    void waitForResponse() noexcept(false);
    void sendMessage(const QString &text);
    bool checkResponse(int code, SmtpError type);

protected:
    QScopedPointer<HSmtpClientPrivate> d_ptr;
};

HE_CONTROL_END_NAMESPACE

#endif // HSMTPCLIENT_H
