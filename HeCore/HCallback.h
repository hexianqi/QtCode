/***************************************************************************************************
**      2020-08-25  HCallback 类回调模板。
***************************************************************************************************/

#pragma once

#include "HCoreGlobal.h"
#include <functional>

HE_CORE_BEGIN_NAMESPACE

template <typename T>
struct HCallback;

template <typename Ret, typename... Params>
struct HCallback<Ret(Params...)>
{
    template <typename... Args>
    static Ret callback(Args... args)
    {
        return func(args...);
    }
    static std::function<Ret(Params...)> func;
};

template <typename Ret, typename... Params>
std::function<Ret(Params...)> HCallback<Ret(Params...)>::func;

// typedef void(*libvlc_callback_t)(const struct libvlc_event_t *event, void *data);
// HCallback<void(const libvlc_event_t *, void *)>::func = std::bind(&HVlcPlayerControl::handleEvents, this, std::placeholders::_1, std::placeholders::_2);
// libvlc_callback_t callback = (HCallback<void(const libvlc_event_t *, void *)>::callback);
// libvlc_event_attach(d_ptr->manager, event, callback, this);
//void HVlcPlayerControl::handleEvents(const libvlc_event_t *event, void */*data*/)
//{
//}

HE_CORE_END_NAMESPACE
