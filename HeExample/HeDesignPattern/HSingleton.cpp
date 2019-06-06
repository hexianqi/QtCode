#include "HSingleton.h"
#include<mutex>

HLazySingleton* HLazySingleton::__instance = nullptr;
HLazySingleton::GC HLazySingleton::GC::gc;
static std::once_flag __oc; // 用于call_once的局部静态变量

HLazySingleton* HLazySingleton::getInstance()
{
    std::call_once(__oc, [&]{ __instance = new HLazySingleton(); });
    return __instance;
}

HLazySingleton::GC::~GC()
{
    // 可以在这里销毁所有的资源，例如：db 连接、文件句柄等
    if (__instance == nullptr)
        return;
    delete __instance;
    __instance = nullptr;
}


std::shared_ptr<HEagerSingleton> HEagerSingleton::__instance(new HEagerSingleton(), HEagerSingleton::destory);

std::shared_ptr<HEagerSingleton> HEagerSingleton::getInstance()
{
    return __instance;
}

void HEagerSingleton::destory(HEagerSingleton *)
{
}

