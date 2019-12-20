/***************************************************************************************************
**      2019-12-20  HChineseHelper 中文帮助类。
***************************************************************************************************/

#ifndef HCHINESEHELPER_H
#define HCHINESEHELPER_H

#include "HControlGlobal.h"
#include <QtCore/QObject>

HE_CONTROL_BEGIN_NAMESPACE

class HChineseHelperPrivate;

class HChineseHelper : public QObject
{
    Q_OBJECT

public:
    static HChineseHelper *instance();

public:
    ~HChineseHelper() override;

public:
    void loadPingYin(const QString &fileName);
    void loadJianPin(const QString &fileName);
    QString toPingYin(const QString &value);
    QString toJianPin(const QString &value);

protected:
    HChineseHelper(QObject *parent = nullptr);
    HChineseHelper(const HChineseHelper&) = delete;
    HChineseHelper &operator=(const HChineseHelper&) = delete;

private:
    void init();

private:
    static QScopedPointer<HChineseHelper> __instance;
    QScopedPointer<HChineseHelperPrivate> d_ptr;
};

HE_CONTROL_END_NAMESPACE

#endif // HCHINESEHELPER_H
