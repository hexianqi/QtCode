/***************************************************************************************************
**      2019-05-29  HLazySingleton 懒汉式单例模式。
**                  https://blog.csdn.net/10km/article/details/49777749
**                  HEagerSingleton 饿汉式单例模式。
**                  https://blog.csdn.net/cjbct/article/details/79266057
***************************************************************************************************/

#pragma once

#include<memory>

class HLazySingleton
{
public:
    static HLazySingleton *getInstance();

protected:
    HLazySingleton() = default;
    ~HLazySingleton() = default;
    HLazySingleton(const HLazySingleton&) = delete;
    HLazySingleton &operator=(const HLazySingleton&) = delete;

protected:
    static HLazySingleton *__instance;

private:
    // GC 机制
    class GC
    {
        public:
            ~GC();

        public:
            static GC gc; // 用于释放单例
    };
};

class HEagerSingleton
{
public:
    static std::shared_ptr<HEagerSingleton> getInstance();

protected:
    HEagerSingleton() = default;
    ~HEagerSingleton() = default;
    HEagerSingleton(const HEagerSingleton&) = delete;
    HEagerSingleton &operator=(const HEagerSingleton&) = delete;

protected:
    static void destory(HEagerSingleton *);

protected:
    static std::shared_ptr<HEagerSingleton> __instance;
};
