#ifndef HREGISTER_H
#define HREGISTER_H

#include "HeAlgorithm_global.h"

#include <QString>

namespace He {
namespace Algorithm {

// 注册机
class HEALGORITHM_EXPORT HRegister
{
public:
    HRegister();

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

private:
    QString _registerId;
    QString _serialNumber;
    int _trialTimes;
    int _firstDate;
};

} // Algorithm
} // He

#endif // HREGISTER_H
