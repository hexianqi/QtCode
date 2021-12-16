#pragma once

#include "HHttpClient.h"
#include <QtCore/QUrlQuery>

HE_BEGIN_NAMESPACE

enum class HHttpClientRequestMethod
{
    GET,
    POST,
    PUT,
    DELETE,
    UPLOAD
};

class HHttpClientPrivateCache
{
public:
    std::function<void (const QString &)> success = nullptr;
    std::function<void (const QString &, int)> fail = nullptr;
    std::function<void ()> complete = nullptr;
    bool debug = false;
    bool internal = false;
    QString charset;
    QNetworkAccessManager* manager = nullptr;
};

class HHttpClientPrivate
{
public:
    HHttpClientPrivate(const QString &url);
    ~HHttpClientPrivate();

public:
    QNetworkAccessManager* getManager();
    HHttpClientPrivateCache cache();

public:
    QString url;                                                // 请求的 URL
    QString json;                                               // 请求的参数使用 Json 格式
    QUrlQuery query;                                            // 请求的参数使用 Form 格式
    QString charset = "UTF-8";                                  // 请求响应的字符集
    QHash<QString, QString> header;                             // 请求头
    QNetworkAccessManager *manager = nullptr;                   // 执行 HTTP 请求的 QNetworkAccessManager 对象
    bool useJson = false;                                       // 为 true 时请求使用 Json 格式传递参数，否则使用 Form 格式传递参数
    bool debug = false;                                         // 为 true 时输出请求的 URL 和参数
    bool internal = true;                                       // 是否使用自动创建的 manager

    std::function<void (const QString &)> success = nullptr;    // 成功的回调函数，参数为响应的字符串
    std::function<void (const QString &, int)> fail = nullptr;  // 失败的回调函数，参数为失败原因和 HTTP status code
    std::function<void ()> complete = nullptr;                  // 结束的回调函数

};

HE_END_NAMESPACE
