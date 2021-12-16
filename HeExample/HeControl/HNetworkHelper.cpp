#include "HNetworkHelper.h"
#include <QtNetwork/QNetworkInterface>

HE_BEGIN_NAMESPACE

QStringList HNetworkHelper::localIP(QAbstractSocket::NetworkLayerProtocol type)
{
    QSet<QString> set;
    for (const auto &i : QNetworkInterface::allInterfaces())
    {
        // 移除虚拟机和抓包工具的虚拟网卡
        auto name = i.humanReadableName().toLower();
        if (name.startsWith("vmware network adapter") || name.startsWith("npcap loopback adapter"))
            continue;
        // 过滤当前网络接口
        if (i.flags() != (QNetworkInterface::IsUp | QNetworkInterface::IsRunning | QNetworkInterface::CanBroadcast | QNetworkInterface::CanMulticast))
            continue;
        for (const auto &addr : i.addressEntries())
        {
            if (addr.ip().protocol() == type)
                set << addr.ip().toString();
        }
    }
    if (type == QAbstractSocket::IPv4Protocol || type == QAbstractSocket::AnyIPProtocol)
        set << "127.0.0.1";
    if (type == QAbstractSocket::IPv6Protocol || type == QAbstractSocket::AnyIPProtocol)
        set << "::1";
    return set.toList();
}

HE_END_NAMESPACE
