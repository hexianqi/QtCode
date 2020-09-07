#include "HTestMedia.h"
#include <vlc/vlc.h>
#include <QtWidgets/QFileDialog>
#include <QtCore/QDebug>

bool HTestMedia::videoPlayer_vlc(QString fileName)
{
    fileName = QFileDialog::getOpenFileUrl(nullptr, "打开文件", QUrl(), "All files (*.*)").toString();
    if (fileName.isEmpty())
        return false;

//    QUrl url;
//    QFileDialog fileDialog;
//    fileDialog.setAcceptMode(QFileDialog::AcceptOpen);
//    fileDialog.setWindowTitle("Open Files");
//    fileDialog.setFilter("All files (*.*)");
//    fileDialog.setDirectory(".");
//    if (fileDialog.exec() == QDialog::Accepted)
//        url = fileDialog.selectedUrls().first();

    auto data = fileName.toUtf8();
    auto path = data.constData();
    qDebug() << path;

    auto instance = libvlc_new(0, nullptr);
    auto media = libvlc_media_new_path(instance, fileName.toUtf8().constData());
//    auto media = libvlc_media_new_location(instance, path);

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
