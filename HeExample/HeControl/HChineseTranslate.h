/***************************************************************************************************
**      2022-05-27  HChineseTranslate 中文转拼音。
***************************************************************************************************/

#pragma once

#include "HNamespace.h"
#include "HeCore/HSingleton3.h"
#include <QtCore/QObject>

HE_BEGIN_NAMESPACE

class HChineseTranslatePrivate;

class HChineseTranslate : public QObject
{
    Q_OBJECT
    H_SINGLETON3(HChineseTranslate)

private:
    explicit HChineseTranslate(QObject *parent = nullptr);
    ~HChineseTranslate() override;

public:
    void loadPinYin(const QString &fileName);
    void loadJianPin(const QString &fileName);
    QString toPingYin(const QString &value);    // 汉字转拼音
    QString toJianPin(const QString &value);    // 汉字转字母简拼
    QString toShouZhiMu(const QString &value);  // 汉字转首字母

protected:
    QScopedPointer<HChineseTranslatePrivate> d_ptr;
};

HE_END_NAMESPACE

