/***************************************************************************************************
**      2021-10-26  HTestProduct
***************************************************************************************************/

#pragma once

#include "HTestData.h"

HE_DATA_BEGIN_NAMESPACE

class HTestProductPrivate;

class HTestProduct : public HTestData
{
    Q_DECLARE_PRIVATE(HTestProduct)

public:
    explicit HTestProduct();
    ~HTestProduct() override;

public:
    QVariant handleOperation(QString type, QVariant value = QVariant()) override;

protected:
    HTestProduct(HTestProductPrivate &);

protected:
    void increase();
    void readSettings(QString fileName);
    void writeSettings(QString fileName);
};

HE_DATA_END_NAMESPACE

