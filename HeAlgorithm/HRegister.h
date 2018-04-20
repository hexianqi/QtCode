#ifndef HREGISTER_H
#define HREGISTER_H

#include "HeAlgorithm_global.h"
#include <QScopedPointer>

class HRegisterPrivate;

namespace He {
namespace Algorithm {

// 注册机
class HEALGORITHM_EXPORT HRegister
{
    Q_DECLARE_PRIVATE(HRegister)
    Q_DISABLE_COPY(HRegister)

public:
    HRegister();
    virtual ~HRegister() = default;

public:
    // 获取注册码
    bool getRegisterCode(QString &registerCode);
    // 设置注册码
    bool setRegisterCode(QString registerCode);
    // 获取注册号
    QString getRegisterId();
     //校验注册码
    bool checkRegisterCode();
    bool checkRegisterCode(QString registerId, QString registerCode);
    // 解密注册号
    QString encrypt(QString registerId);
    // 是否到期
    bool isExpires();
    // 试用
    void trial();

protected:
    HRegister(HRegisterPrivate &dd);

protected:
    QScopedPointer<HRegisterPrivate> d_ptr;
};

} // Algorithm
} // He

#endif // HREGISTER_H
