/***************************************************************************************************
**      2020-06-12  HFFmpegHelper 帮助类。
***************************************************************************************************/

#pragma once

#include "HControlGlobal.h"
#include <QtCore/QVariantMap>

class AVInputFormat;
class AVOutputFormat;
class AVCodec;
class AVFilter;
class AVBitStreamFilter;

HE_CONTROL_BEGIN_NAMESPACE

class HFFmpegHelper
{
public:
    // 初始化
    static void initLib();
    // 信息
    static QVariantMap getInfo();
    // 协议
    static QStringList getProtocol(int output);
    // 解封装器
    static QList<const AVInputFormat *> getDemuxer();
    // 封装器
    static QList<const AVOutputFormat *> getMuxer();
    // 编码器
    static QList<const AVCodec *> getEncoder();
    // 解码器
    static QList<const AVCodec *> getDecoder();
    // 滤镜
    static QList<const AVFilter *> getFilter();
    // BSF
    static QList<const AVBitStreamFilter *> getBSF();
};

HE_CONTROL_END_NAMESPACE

