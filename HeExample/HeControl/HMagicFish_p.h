#ifndef HMAGICFISH_P_H
#define HMAGICFISH_P_H

#include "HMagicFish.h"

HE_CONTROL_BEGIN_NAMESPACE

class HMagicFishPrivate
{
public:
    QColor baseColor = QColor(244, 92, 71);         // 基准颜色
    QColor headColor = QColor(244, 92, 71, 200);    // 鱼头颜色
    QColor bodyColor = QColor(244, 92, 71, 220);    // 鱼身颜色
    QColor finColor = QColor(244, 92, 71, 150);     // 鱼鳍颜色
    QColor tailColor = QColor(244, 92, 71, 180);    // 鱼尾颜色
    bool finMoveEnable = false;                     // 鱼鳍是否摆动
    int speed = 30;                                 // 游动速度即尾巴摆动频率
    double wave = 1.0;                              // 摆动幅度
    double angle = 0.0;                             // 旋转的角度
    int currentValue = 0;                           // 游动的位置
    double headLen;                                 // 鱼头尺寸
    double bodyLen;                                 // 鱼身尺寸
    double finLen;                                  // 鱼鳍尺寸
    double tailLen;                                 // 鱼尾尺寸
    QPointF headPos;                                // 鱼头坐标
    QTimer *timer;
};

HE_CONTROL_END_NAMESPACE

#endif // HMAGICFISH_P_H
