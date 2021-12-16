/***************************************************************************************************
**      2020-03-30  HSingleton2 单例模板。
**                  使用方法:
**                  1. 定义类为单例(类声明时使用宏 SINGLETON):
**                  class Config
**                  {
**                      H_SINGLETON2(Config)
**                  private:
**                      Config();
**                      ~Config();
**                  public:
**                  }
**
**                  2. 调用单例的函数，可以任意使用下面三种方式中的一种:
**                      2.1 推荐调用: Config::instance()->method();
**                      2.2 原始调用: HSingleton2<Config>::instance()->method();
**                      2.3 保存引用，方便多次调用:
**                          auto config = HSingleton2<Config>::instance();
**                          config->method1();
**                          config->method2();
**                          config->method3();
**
**                  注意:
**                      如果单例的类需要释放的资源和Qt底层的信号系统有关系，
**                      例如QSettings的数据没有保存，QSqlDatabase的连接没有关闭等，
**                      需要在main函数返回前手动释放，否则有可能在程序退出时报系统底层的信号错误，
**                      因为main函数返回后qApp已经被回收，
**                      而资源的释放在main返回后，又和信号槽有关，所以就可能报错。
**                      推荐实现方式: 可以在单例类的构造函数中给qApp的aboutToQuit信号绑定一个槽函数，在里面处理善后工作、释放资源等。
***************************************************************************************************/

#pragma once

#include "HNamespace.h"
#include <QMutex>
#include <QScopedPointer>

HE_BEGIN_NAMESPACE

template <typename T>
class HSingleton2
{
public:
    static T *instance();
    static void release();

private:
    HSingleton2(const HSingleton2 &) = delete;
    HSingleton2<T> &operator=(const HSingleton2 &) = delete;

private:
    static QMutex __mutex;
    static QScopedPointer<T> __instance;
};

template <typename T> QMutex HSingleton2<T>::__mutex;
template <typename T> QScopedPointer<T> HSingleton2<T>::__instance;

template <typename T>
T *HSingleton2<T>::instance()
{
    if (__instance.isNull())
    {
        __mutex.lock();
        if (__instance.isNull())
            __instance.reset(new T); // 此指针会在全局变量作用域结束时自动 deleted (main 函数返回后)
        __mutex.unlock();
    }
    return __instance.data();
}

template <typename T>
void HSingleton2<T>::release()
{
    QMutexLocker locker(&__mutex);
    __instance.reset();
}

#define H_SINGLETON2(Class)                         \
private:                                            \
    Class(const Class &) = delete;                  \
    Class &operator=(const Class &) = delete;       \
    friend HSingleton2<Class>;                      \
    friend QScopedPointerDeleter<Class>;            \
                                                    \
public:                                             \
    static Class *instance()                        \
    {                                               \
        return HSingleton2<Class>::instance();      \
    }                                               \
    static void release()                           \
    {                                               \
        HSingleton2<Class>::release();              \
    }

HE_END_NAMESPACE
