#pragma once

#include "HVlcPlayerControl.h"
#include "vlc/vlc.h"

HE_CONTROL_BEGIN_NAMESPACE

class HVlcPlayerControlPrivate
{
public:
    bool opened = false;
    bool fullScreen = false;
    HVlcPlayerControl::State state = HVlcPlayerControl::Stopped;
    QString url;
    QWidget *widget = nullptr;
    libvlc_instance_t *instance = nullptr;              // 载体对象
    libvlc_media_t *media = nullptr;                    // 媒体对象
    libvlc_media_player_t *player = nullptr;            // 播放对象
    libvlc_event_manager_t *mediaManager = nullptr;     // 媒体事件管理器
    libvlc_event_manager_t *playerManager = nullptr;    // 播放事件管理器
    libvlc_callback_t callback = nullptr;               // 回调函数
};

HE_CONTROL_END_NAMESPACE

