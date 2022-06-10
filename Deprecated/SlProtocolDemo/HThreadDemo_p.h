#pragma once

#include "HThreadDemo.h"
#include "HeController/HAbstractThread_p.h"
#include "HeData/HDataGlobal.h"

class HProtocolDemo;
class HTestSpecDemo;

class HThreadDemoPrivate : public HAbstractThreadPrivate
{
public:
    HThreadDemoPrivate();

public:
    HProtocolDemo *protocol;
    HTestSpecDemo *testSpec;
};
