#ifndef HAPPCONTEXT_H
#define HAPPCONTEXT_H

#include "HSingleton.h"
#include <QObject>
#include <QVariant>

class QSettings;

HE_CORE_BEGIN_NAMESPACE

class HAppContextPrivate;

// 应用程序上下文
class HE_CORE_EXPORT HAppContext : public QObject, public HSingleton<HAppContext>
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HAppContext)
    Q_DISABLE_COPY(HAppContext)
    H_FRIEND_SINGLETON(HAppContext)

public:
    // 创建INI配置
    std::shared_ptr<QSettings> createSettings();
    void setSetting(QString fileName);

public:
    // 获取上下文数值
    template<class T>
    T getContextValue(QString key);
    // 获取上下文指针
    template<class T>
    T getContextPointer(QString key);
    // 设置上下文数值
    void setContextValue(QString key, QVariant value);
    // 设置上下文指针
    void setContextPointer(QString key, QObject *value);

protected:
    HAppContext();
    HAppContext(HAppContextPrivate &p);
    ~HAppContext();

protected:
    void initActionComment();
    void initErrorComment();
    void initDataFormatInfo();
    void initDataCaption();
    void readMimeType();

protected:
    QScopedPointer<HAppContextPrivate> d_ptr;
};

extern HE_CORE_EXPORT std::shared_ptr<HAppContext> hApp;

HE_CORE_END_NAMESPACE

#endif // HAPPCONTEXT_H
