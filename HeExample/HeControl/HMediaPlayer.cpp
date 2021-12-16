#include "HMediaPlayer_p.h"

HE_BEGIN_NAMESPACE

HMediaPlayer::HMediaPlayer(QObject *parent) :
    QObject(parent),
    d_ptr(new HMediaPlayerPrivate)
{
}

HMediaPlayer::HMediaPlayer(HMediaPlayerPrivate &p, QObject *parent) :
    QObject(parent),
    d_ptr(&p)
{
}

HMediaPlayer::~HMediaPlayer()
{
}

HE_END_NAMESPACE
