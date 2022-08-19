#pragma once

#include "HGifWidget.h"
#include "include/gif.h"

HE_BEGIN_NAMESPACE

class IEventFilter;

class HGifWidgetPrivate
{
public:
    bool running = false;
    int borderWidth = 3;                        // 边框宽度
    QColor background = QColor(34, 163, 169);   // 背景颜色
    int fps = 10;                               // 帧数（100 = 1s）
    QString fileName;                           // 保存文件名称
    QRect screen;                               // 截屏区域
    QTimer *timer = nullptr;                    // 截屏定时器
    int count = 0;
    Gif *gif = nullptr;
    Gif::GifWriter *gifWriter = nullptr;
    IEventFilter *filter = nullptr;
};

HE_END_NAMESPACE
