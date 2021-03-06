#ifndef HTESTDATA_P_H
#define HTESTDATA_P_H

#include "HTestData.h"

HE_DATA_BEGIN_NAMESPACE

class HTestDataPrivate
{
public:
    void setData(QString type, QVariant value);
    void setData(QVariantMap value);
    void addData(QString type, QVariant value);
    void addData(QVariantMap value);
    QVariant data(QString type);

public:
    ITestData *successor = nullptr;
    QVariantMap datas;
};

HE_DATA_END_NAMESPACE

#endif // HTESTDATA_P_H
