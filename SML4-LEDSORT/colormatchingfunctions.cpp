#include "colormatchingfunctions.h"

ColorMatchingFunctions::ColorMatchingFunctions()
{

}

void ColorMatchingFunctions::xyz2rgb(int &r, int &g, int &b, float x, float y, float z)
{
    // 利用xyz数据计算RGB数据
       double dr = 0.4185 * x - 0.1587 * y - 0.0828 * z;
       double dg = -0.0912 * x + 0.2524 * y + 0.0157 * z;
       double db = 0.0009 * x - 0.0025 * y + 0.1786 * z;

       double max = 0.0;
       max = dr > dg ? dr : dg;
       max = max > db ? max : db;

       // 将数据转换为int型，便于显示使用
       r = (int)((dr / max) * 255 + 0.5);
       g = (int)((dg / max) * 255 + 0.5);
       b = (int)((db / max) * 255 + 0.5);

       // 限制数据所属范围
       r = r > 255 ? 255 : r;
       g = g > 255 ? 255 : g;
       b = b > 255 ? 255 : b;

       r = r < 0 ? 0 : r;
       g = g < 0 ? 0 : g;
       b = b < 0 ? 0 : b;

}
