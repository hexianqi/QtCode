/***************************************************************************************************
**      2020-07-20  IMediaPlayerControl 媒体播放器控制接口
***************************************************************************************************/

#pragma once

#include "HControlGlobal.h"
#include <QtCore/QObject>

HE_CONTROL_BEGIN_NAMESPACE

class IMediaPlayerControl : public QObject
{
    Q_OBJECT

public:
    using QObject::QObject;
};

HE_CONTROL_END_NAMESPACE

