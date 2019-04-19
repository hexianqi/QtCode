/***************************************************************************************************
**      2019-04-17  HAbstractGrade 抽象分级数据类。
***************************************************************************************************/

#ifndef HABSTRACTGRADE_H
#define HABSTRACTGRADE_H

#include "IGrade.h"
#include "HeCore/HCollection.h"

HE_DATA_BEGIN_NAMESPACE

class HAbstractGradePrivate;

class HAbstractGrade : public HCollection<IGradeItem>, public IGrade
{
    Q_DECLARE_PRIVATE(HAbstractGrade)

public:
    explicit HAbstractGrade();
    virtual ~HAbstractGrade();

protected:
    HAbstractGrade(HAbstractGradePrivate &);
};

HE_DATA_END_NAMESPACE

#endif // HABSTRACTGRADE_H
