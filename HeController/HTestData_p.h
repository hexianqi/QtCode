#ifndef HTESTDATA_P_H
#define HTESTDATA_P_H

#include "HTestData.h"

HE_CONTROLLER_BEGIN_NAMESPACE

class HTestDataPrivate
{
public:
    void setData(QString type, QVariant value);
    void addData(QString type, QVariant value);
    QVariant data(QString type);

public:
    ITestData *successor = nullptr;
    QVariantHash datas;
};

HE_CONTROLLER_END_NAMESPACE


#endif // HTESTDATA_P_H
