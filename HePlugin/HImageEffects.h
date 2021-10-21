/***************************************************************************************************
**      2020-03-27  HImageEffects 图像效果
**                  https://qtdebug.com/qtbook-paint-image/
***************************************************************************************************/

#pragma once

class QImage;

class HImageEffects
{
public:
    // 灰度效果
    static QImage gray(QImage image);
    // 复古效果
    static QImage siepa(QImage image);
    // 红色蒙版
    static QImage red(QImage image);
    // 反转效果
    static QImage invert(QImage image);
    // 亮度效果
    static QImage brightness(QImage image, int delta);
    // 暖色调
    static QImage warm(QImage image, int delta);
    // 冷色调
    static QImage cool(QImage image, int delta);
    // 饱和度
    static QImage saturation(QImage image, int delta);
};
