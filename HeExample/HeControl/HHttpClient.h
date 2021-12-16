/***************************************************************************************************
**      2020-04-06  HHttpClient
**                  https://qtdebug.com/qtbook-network-http-httpclient/
**                  对QNetworkAccessManager简单封装的 HTTP 访问客户端，简化 GET、POST、PUT、DELETE、上传、下载等操作。
**                  在执行请求前设置需要的参数和回调函数:
**                      1. 调用header()设置请求头
**                      2. 调用param()设置参数，使用Form表单的方式提交请求，GET请求的query parameters也可以用它设置
**                      3. 调用json()设置JSON字符串的request body，Content-Type 为 application/json，
**                         当然也可以不是 JSON 格式，因使用 request body 的情况多数是使用 JSON 格式传递复杂对象，故命名为 json
**                      4. 调用success()注册请求成功的回调函数
**                      5. 调用fail()注册请求失败的回调函数
**                      6. 调用complete()注册请求结束的回调函数
**                         success(), fail(), complete() 的回调函数是可选的，根据需要注册对应的回调函数，也可以一个都不注册
**                         然后根据请求的类型调用 get(), post(), put(), remove(), download(), upload() 执行 HTTP 请求
**                  默认 HttpClient 会创建一个 QNetworkAccessManager，如果不想使用默认的，调用 manager() 传入即可。
**                  调用 debug(true) 设置为调试模式，输出调试信息如 URL、参数等。
***************************************************************************************************/

#pragma once

#include "HNamespace.h"
#include <QVariant>

class QNetworkAccessManager;

HE_BEGIN_NAMESPACE

class HHttpClientPrivate;

class HHttpClient
{

public:
    explicit HHttpClient(const QString &url);
    virtual ~HHttpClient();

public:
    HHttpClient& manager(QNetworkAccessManager *);
    HHttpClient& debug(bool b);
    HHttpClient& param(const QString &name, const QVariant &value);
    HHttpClient& param(const QVariantMap &);
    HHttpClient& json(const QString &);
    HHttpClient& header(const QString &name, const QString &value);
    HHttpClient& header(const QVariantMap &);
    HHttpClient& charset(const QString &);
    HHttpClient& success(std::function<void (const QString &)> func);
    HHttpClient& fail(std::function<void (const QString &, int)> func);
    HHttpClient& complete(std::function<void ()> func);

public:
    void get();
    void post();
    void put();
    void remove();
    void download(const QString &fileName);
    void upload(const QByteArray &data);
    void upload(const QString &fileName);
    void upload(const QStringList &fileNames);

protected:
    QScopedPointer<HHttpClientPrivate> d_ptr;
};

HE_END_NAMESPACE
