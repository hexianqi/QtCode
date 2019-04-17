#include "HReflectFun.h"

HE_EXAMPLE_BEGIN_NAMESPACE

HReflectFun::HReflectFun(QObject *parent)
    : QObject(parent)
{
}

QVariantMap HReflectFun::process(const QVariantMap &request)
{
    QVariantMap reply;
    QString cmd = request["cmd"].toString();
    if (cmd.isEmpty())
    {
        reply["error"] = "invalid command";
        return reply;
    }

    QString methodName = QString("process_%1").arg(cmd);
    bool bret = metaObject()->invokeMethod(this,
                                           methodName.toLatin1(),
                                           Q_RETURN_ARG(QVariantMap, reply),
                                           Q_ARG(QVariantMap, request) );
    if (!bret)
        reply["error"] = "no available method";
    return reply;

}

QVariantMap HReflectFun::process_set_config(const QVariantMap &request)
{
    QVariantMap reply;
    reply["error"] = "success";

    QString keyname = request["key"].toString();
    if (keyname.isEmpty())
    {
        reply["error"] = "invalid keyname";
        return reply;
    }

    _settings[keyname] = request["value"];
    return reply;
}

QVariantMap HReflectFun::process_get_config(const QVariantMap &request)
{
    QVariantMap reply;
    reply["error"] = "success";

    QString keyname = request["key"].toString();
    if (keyname.isEmpty())
    {
        reply["error"] = "invalid keyname";
        return reply;
    }

    if (_settings.contains(keyname))
    {
        reply["value"] = _settings[keyname];
        return reply;
    }

    reply["error"] = "key not found";
    return reply;
}

QVariantMap HReflectFun::process_get_json(const QVariantMap &)
{
    QVariantMap reply;
    reply["error"] = "success";

    QJsonObject jObj = QJsonObject::fromVariantMap(_settings);
    QJsonDocument jDoc(jObj);

    reply["json"] = jDoc.toJson();
    return reply;
}

void Test()
{
    HReflectFun service;
    QTextStream os(stdout);

    QVariantMap request1;
    request1["cmd"] = "set_config";
    request1["key"] = "search-engine";
    request1["value"] = "www.google.com";
    service.process(request1);

    QVariantMap request2;
    request2["cmd"] = "set_config";
    request2["key"] = "proxy";
    request2["value"] = "192.168.100.1";
    service.process(request2);

    QVariantMap request3;
    request3["cmd"] = "get_config";
    request3["key"] = "proxy";
    QVariantMap reply3 = service.process(request3);
    os << "\nproxy: " << reply3["value"].toString() << endl;

    QVariantMap request4;
    request4["cmd"] = "get_json";
    QVariantMap reply4 = service.process(request4);
    os << "\njson:\n" << reply4["json"].toByteArray() << endl;
}

HE_EXAMPLE_END_NAMESPACE
