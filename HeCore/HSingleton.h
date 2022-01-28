/***************************************************************************************************
**      2018-06-19  HSingleton 单例模板。
***************************************************************************************************/

#pragma once

#include "HNamespace.h"
#include <QMutex>
#include <memory>

HE_BEGIN_NAMESPACE

template <typename T>
class HSingleton
{
public:
    template <typename... Args>
    static T *instance(Args&&... args)
    {
        if(__instance == nullptr)
        {
            __mutex.lock();
            if (__instance == nullptr)
                __instance = new T(std::forward<Args>(args)...);
            __mutex.unlock();
        }
        return __instance;
    }

    static T *getInstance()
    {
        if (__instance == nullptr)
            throw std::logic_error("The instance is not init, Please initialize the instance first.");
        return __instance;
    }

    static void release()
    {
        if (__instance)
        {
            delete __instance;
            __instance = nullptr;
        }
    }

protected:
    HSingleton() = default;
    ~HSingleton() = default;
    HSingleton(const HSingleton &) = delete;
    HSingleton &operator=(const HSingleton &) = delete;

protected:
    static T *__instance;
    static QMutex __mutex;
};

template <typename T> T *HSingleton<T>::__instance = nullptr;
template <typename T> QMutex HSingleton<T>::__mutex;

#define H_FRIEND_SINGLETON(Class)    friend HSingleton<Class>;

HE_END_NAMESPACE
