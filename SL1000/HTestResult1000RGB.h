/***************************************************************************************************
**      2023-02-06  HTestResult1000RGB
***************************************************************************************************/

#pragma once

#include <QtCore/QObject>
#include "HNamespace.h"

HE_BEGIN_NAMESPACE
class ITestData;
HE_END_NAMESPACE
HE_USE_NAMESPACE

class HTestResult1000RGBPrivate;

class HTestResult1000RGB : public QObject
{
    Q_OBJECT

public:
    explicit HTestResult1000RGB(QObject *parent = nullptr);
    ~HTestResult1000RGB() override;

public:
    bool isEmpty(int);
    void clear();
    void update(bool);

protected:
    QScopedPointer<HTestResult1000RGBPrivate> d_ptr;
};



