/***************************************************************************************************
**      2019-05-29  装饰者模式
**                  https://blog.csdn.net/liang19890820/article/details/66973836
***************************************************************************************************/

#pragma once

#include <string>

using namespace std;

// 所有饮料的基类
class IBeverage
{
public:
    // 名称
    virtual string name() = 0;
    // 价钱
    virtual double cost() = 0;
};

/********** 具体的饮料（咖啡）**********/

// 黑咖啡，属于混合咖啡
class HouseBlend : public IBeverage
{
public:
    virtual ~HouseBlend() = default;

public:
    string name() override;
    double cost() override;
};

// 深度烘培咖啡豆
class DarkRoast : public IBeverage
{
public:
    virtual ~DarkRoast() = default;

public:
    string name() override;
    double cost() override;
};

// 调味品
class CondimentDecorator : public IBeverage
{
public:
    CondimentDecorator(IBeverage *);
    virtual ~CondimentDecorator() = default;

public:
    string name() override;
    double cost() override;

protected:
    IBeverage *_beverage;
};

/********** 具体的饮料（调味品）**********/

// 奶油
class Cream : public CondimentDecorator
{
public:
    Cream(IBeverage *);

public:
    string name() override;
    double cost() override;
};

// 摩卡
class Mocha : public CondimentDecorator
{
public:
    Mocha(IBeverage *);

public:
    string name() override;
    double cost() override;
};

// 糖浆
class Syrup : public CondimentDecorator
{
public:
    Syrup(IBeverage *);

public:
    string name() override;
    double cost() override;
};
