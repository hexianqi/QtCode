/***************************************************************************************************
**      2018-06-19  HRegister 注册机类。
***************************************************************************************************/

#ifndef HREGISTER_H
#define HREGISTER_H

#include "HAlgorithmGlobal.h"
#include <QtCore/QScopedPointer>

HE_ALGORITHM_BEGIN_NAMESPACE

class HRegisterPrivate;

class HE_ALGORITHM_EXPORT HRegister
{
public:
    HRegister();
    ~HRegister();

public:
    // 获取注册码
    bool getRegisterCode(QString &registerCode);
    // 设置注册码
    bool setRegisterCode(QString registerCode);
    // 获取注册号
    QString getRegisterId();
    // 校验注册码
    bool checkRegisterCode();
    bool checkRegisterCode(QString registerId, QString registerCode);
    // 解密注册号
    QString encrypt(QString registerId);
    // 是否到期
    bool isExpires();
    // 试用
    void trial();

protected:
    HRegister(HRegisterPrivate &);

protected:
    QScopedPointer<HRegisterPrivate> d_ptr;
};

HE_ALGORITHM_END_NAMESPACE

#endif // HREGISTER_H
