/***************************************************************************************************
**      2020-08-25  HClassCallback 类成员函数作为回调函数模板。
***************************************************************************************************/

#pragma once

#include "HNamespace.h"
#include <functional>

HE_BEGIN_NAMESPACE

template <typename T>
struct HClassCallback;

template <typename Ret, typename... Params>
struct HClassCallback<Ret(Params...)>
{
    template <typename... Args>
    static Ret callback(Args... args)
    {
        return func(args...);
    }
    static std::function<Ret(Params...)> func;
};

template <typename Ret, typename... Params>
std::function<Ret(Params...)> HClassCallback<Ret(Params...)>::func;

// typedef void(*libvlc_callback_t)(const struct libvlc_event_t *event, void *data);
// HClassCallback<void(const libvlc_event_t *, void *)>::func = std::bind(&HVlcPlayerControl::handleEvents, this, std::placeholders::_1, std::placeholders::_2);
// libvlc_callback_t callback = (HClassCallback<void(const libvlc_event_t *, void *)>::callback);
// libvlc_event_attach(d_ptr->manager, event, callback, this);
//void HVlcPlayerControl::handleEvents(const libvlc_event_t *event, void */*data*/)
//{
//}

HE_END_NAMESPACE
