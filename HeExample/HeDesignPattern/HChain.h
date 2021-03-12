/***************************************************************************************************
**      2019-05-30  责任链模式
**                  https://blog.csdn.net/liang19890820/article/details/79077715
***************************************************************************************************/

#pragma once

// 抽象处理者
class IHandler
{
public:
    IHandler();
    virtual ~IHandler() = default;

public:
    void setSuccessor(IHandler *);
    virtual void handleRequest(float days) = 0;

protected:
    IHandler *_successor;  // 后继者
};

// 经理
class Manager : public IHandler
{
public:
    void handleRequest(float days) override;
};

// 总监
class Director : public IHandler
{
public:
    void handleRequest(float days) override;
};

// 总裁
class CEO : public IHandler
{
public:
    void handleRequest(float days) override;
};
