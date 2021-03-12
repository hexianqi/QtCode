/***************************************************************************************************
**      2019-03-04  IMouseStrategy 鼠标策略接口。
***************************************************************************************************/

#pragma once

class QMouseEvent;
class QRectF;

class IMouseStrategy
{
public:
    // 设置有效范围
    virtual bool setValidRegion(QRectF value) = 0;
    // 设置是否启用
    virtual bool setEnable(bool b) = 0;
    // 是否启用
    virtual bool isEnable() = 0;

public:
    // 鼠标按下
    virtual bool mousePressEvent(QMouseEvent *) = 0;
    // 鼠标移动
    virtual bool mouseMoveEvent(QMouseEvent *) = 0;
    // 鼠标释放
    virtual bool mouseReleaseEvent(QMouseEvent *) = 0;
};
