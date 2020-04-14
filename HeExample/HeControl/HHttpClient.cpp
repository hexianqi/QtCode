#include <utility>

#include <utility>

#include <utility>

#include "HHttpClient_p.h"
#include <QtCore/QFile>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QHttpMultiPart>
#include <QtCore/QDebug>

HE_CONTROL_BEGIN_NAMESPACE

// 使用用户设定的 URL、请求头、参数等创建 Request
// 1. 如果是 GET 请求，并且参数不为空，则编码请求的参数，放到 URL 后面
// 2. 调试时输出网址和参数
// 3. 设置 Content-Type
// 4. 添加请求头到 request 中
QNetworkRequest createRequest(HHttpClientPrivate *d, HHttpClientRequestMethod method)
{
    bool get      = method == HHttpClientRequestMethod::GET;
    bool upload   = method == HHttpClientRequestMethod::UPLOAD;
    bool withForm = !get && !upload && !d->useJson; // PUT、POST 或者 DELETE 请求，且 useJson 为 false
    bool withJson = !get && !upload &&  d->useJson; // PUT、POST 或者 DELETE 请求，且 useJson 为 true

    if (get && !d->query.isEmpty())
        d->url += "?" + d->query.toString(QUrl::FullyEncoded);

    if (d->debug)
    {
        qDebug().noquote() << "[网址]" << d->url;
        if (withJson)
        {
            qDebug().noquote() << "[参数]" << d->json;
        }
        else if (withForm || upload)
        {
            auto list = QStringList() << "[参数]";
            for (const auto &v : d->query.queryItems())
                list << QString("       %1=%2").arg(v.first, v.second);
            if (list.size() > 1)
                qDebug().noquote() << list.join("\n");
        }
    }
    if (withForm)
        d->header["Content-Type"] = "application/x-www-form-urlencoded";
    else if (withJson)
        d->header["Content-Type"] = "application/json; charset=utf-8";

    QNetworkRequest request(QUrl(d->url));
    for (auto i = d->header.begin(); i != d->header.end(); ++i)
        request.setRawHeader(i.key().toUtf8(), i.value().toUtf8());
    return request;
}

// 读取服务器响应的数据
QString readReply(QNetworkReply *reply, const QString &charset)
{
    QString result;
    QTextStream in(reply);
    in.setCodec(charset.toUtf8());
    while (!in.atEnd())
        result += in.readLine();
    return result;
}

// 请求结束的处理函数
void handleFinish(HHttpClientPrivateCache cache, QNetworkReply *reply, const QString &successMessage, const QString &failMessage)
{
    if (reply->error() == QNetworkReply::NoError)
    {
        if (cache.debug)
            qDebug().noquote() << QString("[结束] 成功: %1").arg(successMessage);
        if (cache.success != nullptr)
            cache.success(successMessage);
    }
    else
    {
        if (cache.debug)
            qDebug().noquote() << QString("[结束] 失败: %1").arg(failMessage);
        if (cache.fail != nullptr)
            cache.fail(failMessage, reply->error());
    }

    if (cache.complete != nullptr)
        cache.complete();

    if (reply != nullptr)
        reply->deleteLater();

    if (cache.internal && cache.manager != nullptr)
        cache.manager->deleteLater();
}

// 执行请求的辅助函数
// 1. 缓存需要的变量，在 lambda 中使用 = 捕获进行值传递 (不能使用引用 &，因为 d 已经被析构)
// 2. 创建请求需要的变量
// 3. 根据 method 执行不同的请求
// 4. 请求结束时获取响应数据，在 handleFinish 中执行回调函数
void execute(HHttpClientPrivate *d, HHttpClientRequestMethod method)
{
    auto cache = d->cache();
    auto request = createRequest(d, method);
    QNetworkReply *reply = nullptr;

    switch (method)
    {
    case HHttpClientRequestMethod::GET:
        reply = cache.manager->get(request);
        break;
    case HHttpClientRequestMethod::POST:
        reply = cache.manager->post(request, d->useJson ? d->json.toUtf8() : d->query.toString(QUrl::FullyEncoded).toUtf8());
        break;
    case HHttpClientRequestMethod::PUT:
        reply = cache.manager->put(request, d->useJson ? d->json.toUtf8() : d->query.toString(QUrl::FullyEncoded).toUtf8());
        break;
    case HHttpClientRequestMethod::DELETE:
        reply = cache.manager->deleteResource(request);
        break;
    default:
        break;
    }
    QObject::connect(reply, &QNetworkReply::finished, [=] { handleFinish(cache, reply, readReply(reply, cache.charset.toUtf8()), reply->errorString()); });
}

// 使用 GET 进行下载，当有数据可读取时回调 readyRead(), 大多数情况下应该在 readyRead() 里把数据保存到文件
// 1. 缓存需要的变量，在 lambda 中使用 = 捕获进行值传递 (不能使用引用 &，因为 d 已经被析构)
// 2. 创建请求需要的变量，执行请求
// 3. 有数据可读取时回调 readyRead()
// 4. 请求结束时获取响应数据，在 handleFinish 中执行回调函数
void downloadData(HHttpClientPrivate *d, const std::function<void (const QByteArray &)> &readyRead)
{
    auto cache = d->cache();
    auto request = createRequest(d, HHttpClientRequestMethod::GET);
    auto reply =  cache.manager->get(request);
    QObject::connect(reply, &QNetworkReply::readyRead, [=] { readyRead(reply->readAll()); });
    QObject::connect(reply, &QNetworkReply::finished, [=] { handleFinish(cache, reply, "下载完成", reply->errorString()); });
}

// 使用 GET 进行下载，下载的文件保存到fileName
// 1. 打开下载文件，如果打开文件出错，不进行下载
// 2. 给请求结束的回调函数注入关闭释放文件的行为
// 3. 调用下载的重载函数开始下载
void downloadData(HHttpClientPrivate *d, const QString &fileName)
{
    auto file = new QFile(fileName);
    if (!file->open(QIODevice::WriteOnly | QIODevice::Truncate))
    {
        auto text = QString("[错误] 打开文件失败[%1]: %2").arg(file->fileName(), file->errorString());
        if (d->debug)
            qDebug().noquote() << text;
        if (d->fail != nullptr)
            d->fail(text, -1);
        file->close();
        file->deleteLater();
        return;
    }

    auto userComplete = d->complete;
    auto injectedComplete = [=] {
        file->flush();
        file->close();
        file->deleteLater();

        if (userComplete != nullptr)
            userComplete();
    };
    d->complete = injectedComplete;
    downloadData(d, [=](const QByteArray &data) { file->write(data); });
}

// 上传文件或者数据的实现
// 1. 缓存需要的变量，在 lambda 中使用 = 捕获进行值传递 (不能使用引用 &，因为 d 已经被析构)
// 2. 创建 Form 表单的参数 Text Part
// 3. 创建上传的 File Part
//    3.1 使用文件创建 File Part
//    3.2 使用数据创建 File Part
// 4. 创建请求需要的变量，执行请求
// 5. 请求结束时释放 multiPart 和打开的文件，获取响应数据，在 handleFinish 中执行回调函数
void uploadData(HHttpClientPrivate *d, const QStringList &files, const QByteArray &data)
{
    auto cache = d->cache();
    auto multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);
    for (const auto &v : d->query.queryItems())
    {
        QHttpPart part;
        part.setHeader(QNetworkRequest::ContentDispositionHeader, QString("form-data; name=\"%1\"").arg(v.first));
        part.setBody(v.second.toUtf8());
        multiPart->append(part);
    }

    if (!files.isEmpty())
    {
        auto inputName = files.size() == 1 ? "file" : "files";
        for (const auto &fileName : files)
        {
            if (fileName.isEmpty())
                continue;
            auto file = new QFile(fileName, multiPart);
            if (!file->open(QIODevice::ReadOnly))
            {
                auto text = QString("[错误] 打开文件失败[%1]: %2").arg(file->fileName(), file->errorString());
                if (d->debug)
                    qDebug().noquote() << text;
                if (d->fail != nullptr)
                    d->fail(text, -1);
                multiPart->deleteLater();
                return;
            }
            // 单个文件时，name 为服务器端获取文件的参数名，为 file
            // 多个文件时，name 为服务器端获取文件的参数名，为 files
            // 注意: 服务器是 Java 的则用 form-data
            // 注意: 服务器是 PHP  的则用 multipart/form-data
            QHttpPart part;
            part.setHeader(QNetworkRequest::ContentDispositionHeader, QString(R"(form-data; name="%1"; filename="%2")").arg(inputName, file->fileName()));
            part.setBodyDevice(file);
            multiPart->append(part);
        }
    }
    else
    {
        QHttpPart part;
        part.setHeader(QNetworkRequest::ContentDispositionHeader, QString(R"(form-data; name="file"; filename="no-name")"));
        part.setBody(data);
        multiPart->append(part);
    }

    auto request = createRequest(d, HHttpClientRequestMethod::UPLOAD);
    auto reply =  cache.manager->post(request, multiPart);
    QObject::connect(reply, &QNetworkReply::finished, [=] {
        multiPart->deleteLater();
        handleFinish(cache, reply, readReply(reply, cache.charset), reply->errorString());
    });
}

HHttpClientPrivate::HHttpClientPrivate(const QString &url) :
    url(url)
{
}

HHttpClientPrivate::~HHttpClientPrivate()
{
    manager = nullptr;
    success = nullptr;
    fail = nullptr;
    complete = nullptr;
}

QNetworkAccessManager *HHttpClientPrivate::getManager()
{
     return internal ? new QNetworkAccessManager : manager;
}

HHttpClientPrivateCache HHttpClientPrivate::cache()
{
    HHttpClientPrivateCache cache;
    cache.success = success;
    cache.fail = fail;
    cache.complete = complete;
    cache.debug = debug;
    cache.internal = internal;
    cache.charset = charset;
    cache.manager = getManager();
    return cache;
}

HHttpClient::HHttpClient(const QString &url) :
    d_ptr(new HHttpClientPrivate(url))
{

}

HHttpClient::~HHttpClient() = default;

HHttpClient &HHttpClient::manager(QNetworkAccessManager *p)
{
    d_ptr->manager  = p;
    d_ptr->internal = p == nullptr;
    return *this;
}

HHttpClient &HHttpClient::debug(bool b)
{
    d_ptr->debug = b;
    return *this;
}

HHttpClient &HHttpClient::param(const QString &name, const QVariant &value)
{
    d_ptr->query.addQueryItem(name, value.toString());
    return *this;
}

HHttpClient &HHttpClient::param(const QVariantMap &value)
{
    for (auto i = value.begin(); i != value.end(); i++)
        d_ptr->query.addQueryItem(i.key(), i.value().toString());
    return *this;
}

HHttpClient &HHttpClient::json(const QString &value)
{
    d_ptr->json = value;
    d_ptr->useJson = true;
    return *this;
}

HHttpClient &HHttpClient::header(const QString &name, const QString &value)
{
    d_ptr->header[name] = value;
    return *this;
}

HHttpClient &HHttpClient::header(const QVariantMap &value)
{
    for (auto i = value.begin(); i != value.end(); i++)
        d_ptr->header[i.key()] = i.value().toString();
    return *this;
}

HHttpClient &HHttpClient::charset(const QString &value)
{
    d_ptr->charset = value;
    return *this;
}

HHttpClient &HHttpClient::success(std::function<void (const QString &)> func)
{
    d_ptr->success = std::move(func);
    return *this;
}

HHttpClient &HHttpClient::fail(std::function<void (const QString &, int)> func)
{
    d_ptr->fail = std::move(func);
    return *this;
}

HHttpClient &HHttpClient::complete(std::function<void ()> func)
{
    d_ptr->complete = std::move(func);
    return *this;
}

void HHttpClient::get()
{
    execute(d_ptr.data(), HHttpClientRequestMethod::GET);
}

void HHttpClient::post()
{
    execute(d_ptr.data(), HHttpClientRequestMethod::POST);
}

void HHttpClient::put()
{
    execute(d_ptr.data(), HHttpClientRequestMethod::PUT);
}

void HHttpClient::remove()
{
    execute(d_ptr.data(), HHttpClientRequestMethod::DELETE);
}

void HHttpClient::download(const QString &fileName)
{
    downloadData(d_ptr.data(), fileName);
}

void HHttpClient::upload(const QByteArray &data)
{
    uploadData(d_ptr.data(), QStringList(), data);
}

void HHttpClient::upload(const QString &fileName)
{
    upload(QStringList() << fileName);
}

void HHttpClient::upload(const QStringList &fileNames)
{
    uploadData(d_ptr.data(), fileNames, QByteArray());
}

HE_CONTROL_END_NAMESPACE
