#ifndef HMODEL2000_H
#define HMODEL2000_H

#include "HeController/HAbstractModel.h"
#include <QSharedDataPointer>

HE_CONTROLLER_USE_NAMESPACE

class HModel2000Private;

class HModel2000 : public HAbstractModel
{
    Q_DECLARE_PRIVATE(HModel2000)

public:
    explicit HModel2000(QObject *parent = nullptr);
    ~HModel2000();

public:
    virtual void initialize(QVariantMap param) override;
    virtual QString typeName() override;

protected:
    HModel2000(HModel2000Private &p, QObject *parent = nullptr);
};

#endif // HMODEL2000_H
