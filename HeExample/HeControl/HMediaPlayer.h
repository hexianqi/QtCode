/***************************************************************************************************
**      2020-07-20  HMediaPlayer
***************************************************************************************************/

#pragma once

#include "HNamespace.h"
#include <QtCore/QObject>

HE_BEGIN_NAMESPACE

class HMediaPlayerPrivate;

class HMediaPlayer : public QObject
{
    Q_OBJECT

public:
    explicit HMediaPlayer(QObject *parent = nullptr);
    ~HMediaPlayer() override;

protected:
    HMediaPlayer(HMediaPlayerPrivate &p, QObject *parent = nullptr);

protected:
    QScopedPointer<HMediaPlayerPrivate> d_ptr;
};

HE_END_NAMESPACE

