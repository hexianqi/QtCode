/***************************************************************************************************
**      2022-02-11  HTestResult7000
***************************************************************************************************/

#pragma once

#include <QtCore/QObject>
#include "HeData/ITestData.h"

HE_USE_NAMESPACE

class HTestResult7000Private;

class HTestResult7000 : public QObject
{
    Q_OBJECT

public:
    explicit HTestResult7000(QObject *parent = nullptr);
    ~HTestResult7000() override;

public:
    ITestData *at(int i);
    bool isEmpty();
    int size();
    void clear();
    void update();
    void setPolygon(QPolygon);
    void setModified(bool b = true);

protected:
    QScopedPointer<HTestResult7000Private> d_ptr;
};



