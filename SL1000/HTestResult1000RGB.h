/***************************************************************************************************
**      2023-02-06  HTestResult1000RGB
***************************************************************************************************/

#pragma once

#include <QtCore/QObject>

class HTestResult1000RGBPrivate;

class HTestResult1000RGB : public QObject
{
    Q_OBJECT

public:
    explicit HTestResult1000RGB(QObject *parent = nullptr);
    ~HTestResult1000RGB() override;

public:
    void clearResult();

protected:
    QScopedPointer<HTestResult1000RGBPrivate> d_ptr;
};



