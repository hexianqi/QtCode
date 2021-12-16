#pragma once

#include "HSmtpClient.h"

class QTcpSocket;

HE_BEGIN_NAMESPACE

class HSmtpClientPrivate
{
public:
    QTcpSocket *socket = nullptr;
    QString host = "localhost";
    int port = 25;
    HSmtpClient::ConnectionType connectionType = HSmtpClient::Tcp;
    HSmtpClient::AuthMethod authMethod = HSmtpClient::AuthLogin;
    int connectionTimeout = 5000;
    int responseTimeout = 5000;
    int sendTimeout = 60000;
    QString name = "localhost";
    QString user;
    QString password;
    QString responseText;
    int responseCode;
};

HE_END_NAMESPACE
