#include "HReflectFun2.h"
#include <QtCore>

HE_EXAMPLE_BEGIN_NAMESPACE

template <typename T>
class EventHandler : public QObject
{
public:
    using HandlerFuncType = QVariantMap(T::*)(const QVariantMap &);

    static bool AddHandler(QObject *parent, const QString &name, EventHandler<T>::HandlerFuncType function)
    {
        if (!parent || !function || name.isEmpty())
            return false;
        EventHandler<T> *handler = new EventHandler<T>(name, function);
        if (!handler)
            return false;
        // event handler objects are automatically deleted when their parent is deleted
        handler->setParent(parent);
        return true;
    }

    EventHandler<T>::HandlerFuncType function() const { return _function; }

private:
    // disable public constructor
    EventHandler(const QString &name, EventHandler<T>::HandlerFuncType function)
        : _function(function)
    {
        this->setObjectName(name);
    }

    EventHandler<T>::HandlerFuncType _function;
};

using SampleHandler = EventHandler<HReflectFun2>;
#define AddServiceHandler(parent, func) SampleHandler::AddHandler(parent, #func, &HReflectFun2::func)


HReflectFun2::HReflectFun2(QObject *parent)
    : QObject(parent)
{
    AddServiceHandler(this, process_set_config);
    AddServiceHandler(this, process_get_config);
    AddServiceHandler(this, process_get_json);
    SampleHandler::AddHandler(this, "process_set_setting", &HReflectFun2::process_set_config);
    SampleHandler::AddHandler(this, "process_get_setting", &HReflectFun2::process_get_config);
}

QVariantMap HReflectFun2::process(const QVariantMap &request)
{
    QVariantMap reply;

    QString cmd = request["cmd"].toString();
    if (cmd.isEmpty())
    {
        reply["error"] = "invalid command";
        return reply;
    }

    QString handlerName = QString("process_%1").arg(cmd);
    SampleHandler *handler = this->findChild<SampleHandler *>(handlerName, Qt::FindDirectChildrenOnly);
    if (!handler)
    {
        reply["error"] = "no available handler";
        return reply;
    }

    return ((*this).*(handler->function()))(request);
}

QVariantMap HReflectFun2::process_set_config(const QVariantMap &request)
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

QVariantMap HReflectFun2::process_get_config(const QVariantMap &request)
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

QVariantMap HReflectFun2::process_get_json(const QVariantMap &)
{
    QVariantMap reply;
    reply["error"] = "success";

    QJsonObject jObj = QJsonObject::fromVariantMap(_settings);
    QJsonDocument jDoc(jObj);

    reply["json"] = jDoc.toJson();
    return reply;
}

void test()
{
    HReflectFun2 service;
    QTextStream os(stdout);

    QVariantMap request1;
    request1["cmd"] = "set_setting";
    request1["key"] = "search-engine";
    request1["value"] = "www.google.com";
    service.process(request1);

    QVariantMap request2;
    request2["cmd"] = "set_config";
    request2["key"] = "proxy";
    request2["value"] = "192.168.100.1";
    service.process(request2);

    QVariantMap request3;
    request3["cmd"] = "get_setting";
    request3["key"] = "proxy";
    QVariantMap reply3 = service.process(request3);
    os << "\nproxy: " << reply3["value"].toString() << endl;

    QVariantMap request4;
    request4["cmd"] = "get_json";
    QVariantMap reply4 = service.process(request4);
    os << "\njson:\n" << reply4["json"].toByteArray() << endl;
}

HE_EXAMPLE_END_NAMESPACE
