/***************************************************************************************************
**      2022-09-16  HThreadDemo
***************************************************************************************************/

#pragma once

#include "HeController/HAbstractThread.h"

HE_USE_NAMESPACE

class HThreadDemoPrivate;

class HThreadDemo : public HAbstractThread
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HThreadDemo)

public:
    explicit HThreadDemo(QObject *parent = nullptr);
    ~HThreadDemo() override;
};



