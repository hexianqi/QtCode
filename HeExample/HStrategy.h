/***************************************************************************************************
**      2019-05-30  策略模式
**                  https://blog.csdn.net/liang19890820/article/details/79242297
***************************************************************************************************/

#ifndef HSTRATEGY_H
#define HSTRATEGY_H

// 出行策略
class IStrategy
{
public:
    virtual ~IStrategy() = default;

public:
    virtual void travel() = 0;
};

// 骑自行车
class BikeStrategy : public IStrategy
{
public:
    void travel() override;
};

// 开车
class CarStrategy : public IStrategy
{
public:
    void travel() override;
};

// 坐火车
class TrainStrategy : public IStrategy
{
public:
    void travel() override;
};

class Context
{
public:
    Context(IStrategy *);

public:
    void travel();

private:
    IStrategy *_strategy;
};

#endif // HSTRATEGY_H
