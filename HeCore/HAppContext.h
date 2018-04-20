#ifndef HAPPCONTEXT_H
#define HAPPCONTEXT_H

#include "HeCore_global.h"
#include "HSingleton.h"
#include <QObject>
#include <QVariant>

class QSettings;

namespace He {
namespace Core {

// 应用程序上下文
class HECORE_EXPORT HAppContext : public QObject, public HSingleton<HAppContext>
{
    Q_OBJECT
    H_FRIEND_SINGLETON(HAppContext)

protected:
    HAppContext(QObject *parent = 0);

public:
    // 创建INI配置
    std::shared_ptr<QSettings> createSettings(QObject *parent);
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
    void initActionComment();
    void initErrorComment();
    void initDataFormatInfo();
    void initDataCaption();
    void initMimeType();
    void readMimeType(const QString &filename);

protected:
    QHash<QString, QVariant> _contextValue;
    QHash<QString, QObject*> _contextPointer;
};

extern std::shared_ptr<HAppContext> hApp;

}
}

#endif // HAPPCONTEXT_H
