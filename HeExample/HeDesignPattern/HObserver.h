/***************************************************************************************************
**      2019-05-30  观察者模式
**                  https://blog.csdn.net/liang19890820/article/details/61925314
***************************************************************************************************/

#ifndef HOBSERVER_H
#define HOBSERVER_H

#include <string>
#include <list>

using namespace std;

// 抽象观察者
class IObserver
{
public:
    // 更新价格
    virtual void update(float price) = 0;
};

// 具体观察者
class ConcreteObserver : public IObserver
{
public:
    ConcreteObserver(string name);
    virtual ~ConcreteObserver() = default;

public:
    void update(float price) override;

private:
     string _name;
};

// 抽象主题
class ISubject
{
public:
    // 注册观察者
    virtual void attach(IObserver *) = 0;
    // 注销观察者
    virtual void detach(IObserver *) = 0;
    // 通知观察者
    virtual void notify() = 0;
};

// 具体主题
class ConcreteSubject : public ISubject
{
public:
    ConcreteSubject();
    virtual ~ConcreteSubject() = default;

public:
    void setPrice(float value);
    void attach(IObserver *) override;
    void detach(IObserver *) override;
    void notify() override;

private:
    list<IObserver *> _observers;   // 观察者列表
    float _price;                 // 价格
};

#endif // HOBSERVER_H
