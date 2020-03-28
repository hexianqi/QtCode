#include "HImageEffects.h"
#include <QtGui/QImage>
#include <functional>

// 把图片上每一个像素的颜色转换为函数 process() 的计算结果
void convert(QImage *image, std::function<QColor(QColor)> process)
{
    int w = image->width();
    int h = image->height();
    for (int y = 0; y < h; y++)
    {
        auto line = reinterpret_cast<QRgb *>(image->scanLine(y));
        for (int x = 0; x < w; x++)
        {
            auto color = process(QColor(line[x]));
            image->setPixelColor(x, y, color);
        }
    }
}

// 灰度效果：将图像转成了黑白形式。取红绿蓝像素值的算术平均值。
QImage HImageEffects::gray(QImage image)
{
    convert(&image, [](QColor c) {
        int rr = (c.red() + c.green() + c.blue()) / 3;   // qGray(r, g, b);
        return QColor(rr, rr, rr, c.alpha());
    });
    return image;
}

// 复古效果：让图像呈现一种古旧的效果。分别取红绿蓝像素值的某种加权平均值，。
QImage HImageEffects::siepa(QImage image)
{
    convert(&image, [](QColor c) {
        int r = c.red() * 0.393 + c.green() * 0.769 + c.blue() * 0.189;
        int g = c.red() * 0.349 + c.green() * 0.686 + c.blue() * 0.168;
        int b = c.red() * 0.272 + c.green() * 0.534 + c.blue() * 0.131;
        return QColor(r, g, b, c.alpha());
    });
    return image;
}

// 红色蒙版：让图像呈现一种偏红的效果。将红色通道设为红绿蓝三个值的平均值，而将绿色和蓝色通道都设为0。
QImage HImageEffects::red(QImage image)
{
    convert(&image, [](QColor c) {
        return QColor((c.red() + c.green() + c.blue()) / 3, 0, 0, c.alpha());
    });
    return image;
}

// 反转效果：让图像呈现一种色彩颠倒的效果。将红绿蓝通道都取各自的相反值(255-原值)。
QImage HImageEffects::invert(QImage image) {
    convert(&image, [](QColor c) {
        return QColor(255 - c.red(), 255 - c.green(), 255 - c.blue(), c.alpha());
    });
    return image;
}

// 亮度效果：让图像变得更亮或更暗。将红绿蓝通道，加上一个值。
QImage HImageEffects::brightness(QImage image, int delta) {
    convert(&image, [=](QColor c) {
        int r = qBound(0, c.red() + delta, 255);
        int g = qBound(0, c.green() + delta, 255);
        int b = qBound(0, c.blue() + delta, 255);
        return QColor(r, g, b, c.alpha());
    });
    return image;
}

// 暖色调：让图像变得更黄。将红绿通道，加上一个值，蓝色通道值不变。
QImage HImageEffects::warm(QImage image, int delta)
{
    convert(&image, [=](QColor c) {
        int r = qBound(0, c.red() + delta, 255);
        int g = qBound(0, c.green() + delta, 255);
        return QColor(r, g, c.blue(), c.alpha());
    });
    return image;
}

// 暖色调：让图像变得更蓝。将蓝色通道，加上一个值，红绿通道值不变。
QImage HImageEffects::cool(QImage image, int delta)
{
    convert(&image, [=](QColor c) {
        int b = qBound(0, c.blue() + delta, 255);
        return QColor(c.red(), c.green(), b, c.alpha());
    });
    return image;
}

// 饱和度：让图像变得更加生动。HSL格式，将饱和度通道，加上一个值，色相明度道值不变。
QImage HImageEffects::saturation(QImage image, int delta)
{
    convert(&image, [=](QColor c) {
        int s = qBound(0, c.hslSaturation() + delta, 255);
        return QColor::fromHsl(c.hslHue(), s, c.lightness(), c.alpha());
    });
    return image;
}
