/***************************************************************************************************
**      2022-05-27  HChineseConvert 中文转拼音。
***************************************************************************************************/

#pragma once

#include "HNamespace.h"
#include "HeCore/HSingleton3.h"
#include <QtCore/QObject>

HE_BEGIN_NAMESPACE

class HChineseConvertPrivate;

class HChineseConvert : public QObject
{
    Q_OBJECT
    H_SINGLETON3(HChineseConvert)

private:
    explicit HChineseConvert(QObject *parent = nullptr);
    ~HChineseConvert() override;

public:
    void loadPinYin(const QString &fileName);
    void loadJianPin(const QString &fileName);
    QString toPingYin(const QString &value);    // 汉字转拼音
    QString toJianPin(const QString &value);    // 汉字转字母简拼
    QString toShouZhiMu(const QString &value);  // 汉字转首字母

protected:
    QScopedPointer<HChineseConvertPrivate> d_ptr;
};

HE_END_NAMESPACE

