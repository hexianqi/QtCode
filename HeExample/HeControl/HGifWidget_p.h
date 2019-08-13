#ifndef HGIFWIDGET_P_H
#define HGIFWIDGET_P_H

#include "HGifWidget.h"
#include "include/gif.h"

HE_CONTROL_BEGIN_NAMESPACE

class IEventFilter;

class HGifWidgetPrivate
{
public:
    bool isStart = false;
    int borderWidth = 3;                        // 边框宽度
    QColor background = QColor(34, 163, 169);   // 背景颜色
    int fps = 10;                               // 帧数 100为1s
    QString fileName;                           // 保存文件名称
    QRect screen;                               // 截屏区域
    QTimer *timer = nullptr;                        // 截屏定时器
    Gif *gif = nullptr;
    Gif::GifWriter *gifWriter = nullptr;
    IEventFilter *filter = nullptr;
};

HE_CONTROL_END_NAMESPACE

#endif // HGIFWIDGET_P_H
