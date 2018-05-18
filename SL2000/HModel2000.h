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

protected:
    HModel2000(HModel2000Private &p, QObject *parent = nullptr);

public:
    virtual bool initConfig();
};

#endif // HMODEL2000_H
