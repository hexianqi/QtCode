#pragma once

#include "HChatWidget.h"
#include <QtCore/QMap>

HE_BEGIN_NAMESPACE

struct HChatInfo//聊天信息
{
    HChatInfo(QString userName, QString message);
    QString message;
    QString userName;
};

class HChatWidgetPrivate
{
public:
    QMap<QString, QPixmap> heads;
    QString userName;
    QList<HChatInfo> chats;
};

HE_END_NAMESPACE
