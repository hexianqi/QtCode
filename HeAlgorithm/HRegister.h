/***************************************************************************************************
**      2018-06-19  HRegister 注册机类。
***************************************************************************************************/

#ifndef HREGISTER_H
#define HREGISTER_H

#include "HAlgorithmGlobal.h"
#include <QtCore/QObject>

HE_ALGORITHM_BEGIN_NAMESPACE

class HRegisterPrivate;

class HE_ALGORITHM_EXPORT HRegister : QObject
{
    Q_OBJECT

public:
    HRegister(QObject *parent = nullptr);
    ~HRegister() override;

public:
    // 获取注册号
    QString registerId();
    // 获取注册码
    QString registerCode();
    // 是否到期
    bool isExpires();

public:
    // 设置注册码
    bool setRegisterCode(const QString &value);
    // 校验注册码
    bool check();
    bool check(const QString &id, const QString &code);
    // 解密注册号
    QString encrypt(QString id);

    // 试用
    void trial();

protected:
    HRegister(HRegisterPrivate &p, QObject *parent = nullptr);

protected:
    QScopedPointer<HRegisterPrivate> d_ptr;
};

HE_ALGORITHM_END_NAMESPACE

#endif // HREGISTER_H
