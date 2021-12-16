#pragma once

#include "HNamespace.h"
#include <QScopedPointer>
#include <mutex>

HE_BEGIN_NAMESPACE

template <typename T>
class HSingleton3
{
public:
    static T *instance();

private:
    HSingleton3(const HSingleton3 &) = delete;
    HSingleton3<T> &operator=(const HSingleton3 &) = delete;

private:
    static QScopedPointer<T> __instance;
};

template <typename T> QScopedPointer<T> HSingleton3<T>::__instance;
static std::once_flag __oc; // 用于call_once的局部静态变量

template <typename T>
T *HSingleton3<T>::instance()
{
    std::call_once(__oc, [&]{ __instance.reset(new T); });
    return __instance.data();
}

#define H_SINGLETON3(Class)                         \
private:                                            \
    Class(const Class &) = delete;                  \
    Class &operator=(const Class &) = delete;       \
    friend HSingleton3<Class>;                      \
    friend QScopedPointerDeleter<Class>;            \
                                                    \
public:                                             \
    static Class *instance()                        \
    {                                               \
        return HSingleton3<Class>::instance();      \
    }

HE_END_NAMESPACE
