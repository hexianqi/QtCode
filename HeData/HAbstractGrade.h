/***************************************************************************************************
**      2019-04-17  HAbstractGrade 抽象分级数据类。
***************************************************************************************************/

#ifndef HABSTRACTGRADE_H
#define HABSTRACTGRADE_H

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
    QVariant levels(QString type) override;

protected:
    HAbstractGrade(HAbstractGradePrivate &);
};

HE_DATA_END_NAMESPACE

#endif // HABSTRACTGRADE_H
