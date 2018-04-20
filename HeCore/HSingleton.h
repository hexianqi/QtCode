#ifndef HSINGLETON_H
#define HSINGLETON_H

#include <memory>

namespace He {
namespace Core {

// 单例模板
template <typename T>
class HSingleton
{
public:
    template<typename... Args>
    static T *instance(Args&&... args)
    {
        if(__instance == nullptr)
            __instance = new T(std::forward<Args>(args)...);
        return __instance;
    }

    static T *getInstance()
    {
        if (__instance == nullptr)
            throw std::logic_error("the instance is not init, please initialize the instance first");
        return __instance;
    }

    static void DestroyInstance()
    {
        delete __instance;
        __instance = nullptr;
    }

protected:
    HSingleton() = default;
    ~HSingleton() = default;
    HSingleton(const HSingleton&) = delete;
    HSingleton& operator = (const HSingleton&) = delete;

protected:
    static T *__instance;
};

template <class T>
T *HSingleton<T>::__instance = nullptr;

#define H_FRIEND_SINGLETON(theClass) \
    friend class HSingleton<theClass>;

} // Core
} // He

#endif // HSINGLETON_H
