#include "HSmtpClient_p.h"
#include "HEmailAddress.h"
#include "HMimeMessage.h"
#include <QtCore/QException>
#include <QtNetwork/QSslSocket>

HE_CONTROL_BEGIN_NAMESPACE

class HResponseTimeoutException : public QException
{
};

class HSendMessageTimeoutException : public QException
{
};

HSmtpClient::HSmtpClient(const QString &host, int port, ConnectionType type, QObject *parent) :
    QObject(parent),
    d_ptr(new HSmtpClientPrivate)
{
    d_ptr->socket = new QTcpSocket(this);
    setHost(host);
    setPort(port);
    setConnectionType(type);
}

HSmtpClient::~HSmtpClient()
{
    close();
}

QString HSmtpClient::host() const
{
    return d_ptr->host;
}

int HSmtpClient::port() const
{
    return d_ptr->port;
}

HSmtpClient::ConnectionType HSmtpClient::connectionType() const
{
    return d_ptr->connectionType;
}

HSmtpClient::AuthMethod HSmtpClient::authMethod() const
{
    return d_ptr->authMethod;
}

int HSmtpClient::connectionTimeout() const
{
    return d_ptr->connectionTimeout;
}

int HSmtpClient::responseTimeout() const
{
    return d_ptr->responseTimeout;
}

int HSmtpClient::sendTimeout() const
{
    return d_ptr->sendTimeout;
}

QString HSmtpClient::name() const
{
    return d_ptr->name;
}

QString HSmtpClient::user() const
{
    return d_ptr->user;
}

QString HSmtpClient::password() const
{
    return d_ptr->password;
}

QString HSmtpClient::responseText() const
{
    return d_ptr->responseText;
}

int HSmtpClient::responseCode() const
{
    return d_ptr->responseCode;
}

void HSmtpClient::setHost(const QString &value)
{
    if (d_ptr->host == value)
        return;
    d_ptr->host = value;
}

void HSmtpClient::setPort(int value)
{
    if (d_ptr->port == value)
        return;
    d_ptr->port = value;
}

void HSmtpClient::setConnectionType(ConnectionType value)
{
    if (d_ptr->connectionType == value)
        return;
    d_ptr->connectionType = value;

    close();
    if (d_ptr->connectionType == Tcp)
        d_ptr->socket = new QTcpSocket(this);
    else
        d_ptr->socket = new QSslSocket(this);
}

void HSmtpClient::setAuthMethod(AuthMethod value)
{
    if (d_ptr->authMethod == value)
        return;
    d_ptr->authMethod = value;
}

void HSmtpClient::setConnectionTimeout(int msec)
{
    if (d_ptr->connectionTimeout == msec)
        return;
    d_ptr->connectionTimeout = msec;
}

void HSmtpClient::setResponseTimeout(int msec)
{
    if (d_ptr->responseTimeout == msec)
        return;
    d_ptr->responseTimeout = msec;
}

void HSmtpClient::setSendTimeout(int msec)
{
    if (d_ptr->sendTimeout == msec)
        return;
    d_ptr->sendTimeout = msec;
}

void HSmtpClient::setName(const QString &value)
{
    if (d_ptr->name == value)
        return;
    d_ptr->name = value;
}

void HSmtpClient::setUser(const QString &value)
{
    if (d_ptr->user == value)
        return;
    d_ptr->user = value;
}

void HSmtpClient::setPassword(const QString &value)
{
    if (d_ptr->password == value)
        return;
    d_ptr->password = value;
}

bool HSmtpClient::connectToHost()
{
    if (d_ptr->connectionType == Ssl)
        qobject_cast<QSslSocket *>(d_ptr->socket)->connectToHostEncrypted(d_ptr->host, d_ptr->port);
    else
        d_ptr->socket->connectToHost(d_ptr->host, d_ptr->port);

    if (!d_ptr->socket->waitForConnected(d_ptr->connectionTimeout))
    {
        emit error(ConnectionTimeout);
        return false;
    }

    try
    {
        // If the response code is not 220 (Service ready)
        // means that is something wrong with the server
        waitForResponse();
        if (!checkResponse(220, ServerError))
            return false;
        // Send a EHLO/HELO message to the server
        // The client's first command must be EHLO/HELO
        // The response code needs to be 250.
        sendMessage("EHLO " + d_ptr->name);
        waitForResponse();
        if (!checkResponse(250, ServerError))
            return false;

        if (d_ptr->connectionType == Tls)
        {
            // send a request to start TLS handshake
            // The response code needs to be 220.
            sendMessage("STARTTLS");
            waitForResponse();
            if (!checkResponse(220, ServerError))
                return false;

            auto ssl = qobject_cast<QSslSocket *>(d_ptr->socket);
            ssl->startClientEncryption();
            if (!ssl->waitForEncrypted(d_ptr->connectionTimeout))
            {
                qDebug() << ssl->errorString();
                emit error(ConnectionTimeout);
                return false;
            }
            // Send ELHO one more time
            // The response code needs to be 250.
            sendMessage("EHLO " + d_ptr->name);
            waitForResponse();
            if (!checkResponse(250, ServerError))
                return false;
        }
    }
    catch (HSendMessageTimeoutException &)
    {
         return false;
    }
    catch (HResponseTimeoutException &)
    {
        return false;
    }
    return true;
}

bool HSmtpClient::login()
{
    return login(d_ptr->user, d_ptr->password, d_ptr->authMethod);
}

bool HSmtpClient::login(const QString &user, const QString &password, HSmtpClient::AuthMethod method)
{
    try
    {
        if (method == AuthPlain)
        {
            // Sending command: AUTH PLAIN base64('\0' + username + '\0' + password)
            // The response code needs to be 235.
            sendMessage("AUTH PLAIN " + QByteArray().append('\0').append(user).append('\0').append(password).toBase64());
            waitForResponse();
            if (!checkResponse(235, AuthenticationFailed))
                return false;
        }
        if (method == AuthLogin)
        {
            // Sending command: AUTH LOGIN
            // The response code needs to be 334.
            sendMessage("AUTH LOGIN");
            waitForResponse();
            if (!checkResponse(334, AuthenticationFailed))
                return false;
            // Send the username in base64
            // The response code needs to be 334.
            sendMessage(QByteArray().append(user).toBase64());
            waitForResponse();
            if (!checkResponse(334, AuthenticationFailed))
                return false;
            // Send the password in base64
            // The response code needs to be 235.
            sendMessage(QByteArray().append(password).toBase64());
            waitForResponse();
            if (!checkResponse(235, AuthenticationFailed))
                return false;
        }
    }
    catch (HResponseTimeoutException &)
    {
        emit error(AuthenticationFailed);
        return false;
    }
    catch (HSendMessageTimeoutException &)
    {
        emit error(AuthenticationFailed);
        return false;
    }
    return true;
}

bool HSmtpClient::sendMail(HMimeMessage *value)
{
    try
    {
        // Send the MAIL command with the sender
        sendMessage(QString("MAIL FROM:<%1>").arg(value->sender()->address()));
        waitForResponse();
        if (d_ptr->responseCode != 250)
            return false;
         // Send RCPT command for each recipient
        for (auto i : value->recipients())
        {
            sendMessage(QString("RCPT TO:<%1>").arg(i->address()));
            waitForResponse();
            if (d_ptr->responseCode != 250)
                return false;
        }
        // Send DATA command
        sendMessage("DATA");
        waitForResponse();
        if (d_ptr->responseCode != 354)
            return false;
        // Send DATA
        sendMessage(value->toString());
        // Send \r\n.\r\n to end the mail data
        sendMessage(".");
        waitForResponse();
        if (d_ptr->responseCode != 250)
            return false;
    }
    catch (HResponseTimeoutException &)
    {
        return false;
    }
    catch (HSendMessageTimeoutException &)
    {
        return false;
    }
    return true;
}

void HSmtpClient::quit()
{
    try
    {
        sendMessage("QUIT");
    }
    catch(HSendMessageTimeoutException &)
    {
        // Manually close the connection to the smtp server if message "QUIT" wasn't received by the smtp server
        auto state = d_ptr->socket->state();
        if(state == QAbstractSocket::ConnectedState || state == QAbstractSocket::ConnectingState || state == QAbstractSocket::HostLookupState)
            d_ptr->socket->disconnectFromHost();
    }
}

void HSmtpClient::close()
{
    if (d_ptr->socket != nullptr)
    {
        d_ptr->socket->close();
        d_ptr->socket = nullptr;
    }
}

void HSmtpClient::waitForResponse()
{
    do {
        if (!d_ptr->socket->waitForReadyRead(d_ptr->responseTimeout))
        {
            emit error(ResponseTimeout);
            throw HResponseTimeoutException();
        }

        while (d_ptr->socket->canReadLine())
        {
            // Save the server's response
            d_ptr->responseText = d_ptr->socket->readLine();
            // Extract the respose code from the server's responce (first 3 digits)
            d_ptr->responseCode = d_ptr->responseText.leftRef(3).toInt();
            if (d_ptr->responseCode / 100 == 4)
                emit error(ServerError);
            if (d_ptr->responseCode / 100 == 5)
                emit error(ClientError);
            if (d_ptr->responseText[3] == ' ')
                return;
        }
    } while (true);
}

void HSmtpClient::sendMessage(const QString &text)
{
    d_ptr->socket->write(text.toUtf8() + "\r\n");
    if (!d_ptr->socket->waitForBytesWritten(d_ptr->sendTimeout))
    {
        emit error(SendTimeout);
        throw HSendMessageTimeoutException();
    }
}

bool HSmtpClient::checkResponse(int code, SmtpError type)
{
    if (d_ptr->responseCode == code)
        return true;
    emit error(type);
    return false;
}

HE_CONTROL_END_NAMESPACE
