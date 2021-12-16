#include "HFFPlayerControl_p.h"
#include "HFFPlayerService.h"

HE_BEGIN_NAMESPACE

//HFFPlayerControlPrivate::HFFPlayerControlPrivate(HFFPlayerService *service)
//{
//    this->service = service;
//}

//HFFPlayerControl::HFFPlayerControl(HFFPlayerService *service, QObject *parent) :
//    QObject(parent),
//    d_ptr(new HFFPlayerControlPrivate(service))
//{
//}

//HFFPlayerControl::~HFFPlayerControl()
//{
//}

//bool HFFPlayerControl::setMedia(const QString &value)
//{
//    if (!d_ptr->service->load(value))
//        return false;
//    d_ptr->media = value;
//    emit mediaChanged(d_ptr->media);
//    return true;
//}

//void HFFPlayerControl::play()
//{
//    playOrPause(Playing);
//}

//void HFFPlayerControl::pause()
//{
//    playOrPause(Paused);
//}

//void HFFPlayerControl::stop()
//{
//    d_ptr->service->stop();
//    d_ptr->playerStatus = Stopped;
//    emit statusChanged(Stopped);
//}

//void HFFPlayerControl::updateStatus(PlayerStatus value)
//{
//    if (d_ptr->playerStatus == value)
//        return;
//    d_ptr->playerStatus = value;
//    emit statusChanged(value);
//}

//void HFFPlayerControl::playOrPause(PlayerStatus value)
//{
//    if (d_ptr->mediaStatus == No || value == Stopped || value == d_ptr->playerStatus)
//        return;
//    d_ptr->playerStatus = value;
//    if (value == Paused)
//        d_ptr->service->pause();
//    else
//        d_ptr->service->play();
//    emit statusChanged(value);
//}

HE_END_NAMESPACE
