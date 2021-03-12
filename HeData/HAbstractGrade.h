/***************************************************************************************************
**      2019-04-17  HAbstractGrade 抽象分级数据类。
***************************************************************************************************/

#pragma once

#include "IGrade.h"

HE_DATA_BEGIN_NAMESPACE

class HAbstractGradePrivate;

class HAbstractGrade : public IGrade
{
    Q_DECLARE_PRIVATE(HAbstractGrade)

public:
    explicit HAbstractGrade();
    virtual ~HAbstractGrade() = default;

public:
    void readContent(QDataStream &) override;
    void writeContent(QDataStream &) override;

public:
    void setData(QString name, QVariant value) override;
    QVariant data(QString name) override;

public:
    QVariant levels(QString type) override;

protected:
    HAbstractGrade(HAbstractGradePrivate &);
};

HE_DATA_END_NAMESPACE
