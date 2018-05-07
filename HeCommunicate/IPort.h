#ifndef IPORT_H
#define IPORT_H

#include "HCommunicateGlobal.h"
#include "HeCore/HErrorType.h"
#include <QVariant>

HE_CORE_USE_NAMESPACE

HE_COMMUNICATE_BEGIN_NAMESPACE

class HE_COMMUNICATE_EXPORT IPort
{
public:
    // 初始化
    virtual void initialize(QVariantMap param) = 0;
    // 是否连接
    virtual bool isConnected() = 0;
    // 打开
    virtual HErrorType open(int portNum = 1) = 0;
    // 关闭
    virtual HErrorType close() = 0;
    // 写数据
    virtual HErrorType write(QVector<uchar> data) = 0;
    // 读数据
    virtual HErrorType read(QVector<uchar> &data) = 0;
    // 传输数据
    virtual HErrorType transport(QVector<uchar> &downData, QVector<uchar> &upData, int delay = 0) = 0;
    // 清空缓存
    virtual HErrorType clear() = 0;
};

HE_COMMUNICATE_END_NAMESPACE

#endif // IPORT_H
