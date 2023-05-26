/***************************************************************************************************
**      2018-06-19  IPort 端口接口。
***************************************************************************************************/

#pragma once

#include "HeCore/IInitializeable.h"

HE_BEGIN_NAMESPACE

class IPort : public IInitializeable
{
public:
    // 端口类型
    virtual QString portType() = 0;
    // 是否连接
    virtual bool isConnected() = 0;
    // 设置超时
    virtual void setTimeOut(int value) = 0;
    // 打开
    virtual bool open(int num = 1) = 0;
    // 关闭
    virtual bool close() = 0;
    // 清空缓存
    virtual bool clear() = 0;
    // 写数据
    virtual int write(QVector<uchar> data) = 0;
    // 读数据
    virtual int read(QVector<uchar> &data) = 0;
    // 传输数据
    virtual bool transport(QVector<uchar> &downData, QVector<uchar> &upData, int delay = 0) = 0;
};

HE_END_NAMESPACE
