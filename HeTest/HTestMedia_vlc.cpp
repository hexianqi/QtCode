#include "HTestMedia.h"
#include <vlc/vlc.h>
#include <QtCore/QDebug>

bool HTestMedia::videoPlayer_vlc(QString fileName)
{
    auto instance = libvlc_new(0, nullptr);
    auto media = libvlc_media_new_path(instance, fileName.toStdString().c_str());
    // media = libvlc_media_new_location(instance, rtspMrl);

    auto player = libvlc_media_player_new_from_media(media);

    libvlc_media_player_play(player);

    libvlc_state_t state;
    do
    {
        state = libvlc_media_player_get_state(player);
    } while (state != libvlc_Error && state != libvlc_Ended);

    libvlc_media_player_release(player);
    libvlc_media_release(media);
    libvlc_release(instance);
    return true;
}
