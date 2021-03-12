/***************************************************************************************************
**      2019-05-30  中介者模式
**                  https://blog.csdn.net/liang19890820/article/details/79242388
***************************************************************************************************/

#pragma once

#include <list>
#include <string>

using namespace std;

class IColleague;

// 抽象中介者
class IMediator
{
public:
    // 注册参与者
    virtual void registerColleague(IColleague *);
    // 获取参与者
    virtual const list<IColleague *>& getColleagues() const;
    // 将发送者的消息发送给所有参与者（但不包括发送者自己）
    virtual void distributeMessage(const IColleague *sender, const string &message) const = 0;

private:
    list<IColleague *> _colleagues;
};

// 具体中介者
class ConcreteMediator : public IMediator
{
public:
    void distributeMessage(const IColleague *sender, const string &message) const override;
};

// 抽象同事类
class IColleague
{
public:
    IColleague(const string&);

public:
    string getName() const;
    // 通过中介者，将自己的消息发布出去
    virtual void sendMessage(const IMediator &mediator, const string &message) const = 0;
    // 接收来自发送者的消息
    virtual void receiveMessage(const IColleague *sender, const string &message) const = 0;

private:
    string _name;
};

// 具体同事类
class ConcreteColleague : public IColleague
{
public:
    using IColleague::IColleague;
    virtual ~ConcreteColleague() = default;

public:
    void sendMessage(const IMediator &mediator, const string &message) const override;
    void receiveMessage(const IColleague *sender, const string &message) const override;
};
