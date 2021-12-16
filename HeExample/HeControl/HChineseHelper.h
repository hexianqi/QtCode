/***************************************************************************************************
**      2019-12-20  HChineseHelper 中文帮助类。
***************************************************************************************************/

#pragma once

#include "HNamespace.h"
#include "HeCore/HSingleton3.h"

HE_BEGIN_NAMESPACE

class HChineseHelperPrivate;

class HChineseHelper
{
    H_SINGLETON3(HChineseHelper)

private:
    HChineseHelper();
    ~HChineseHelper();

public:
    void loadPingYin(const QString &fileName);
    void loadJianPin(const QString &fileName);
    QString toPingYin(const QString &value);
    QString toJianPin(const QString &value);

private:
    void init();

private:
    QScopedPointer<HChineseHelperPrivate> d_ptr;
};

HE_END_NAMESPACE
