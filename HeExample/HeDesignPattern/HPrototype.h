/***************************************************************************************************
**      2019-05-29  原型模式
**                  https://blog.csdn.net/liang19890820/article/details/66969965
***************************************************************************************************/

#pragma once

#include <string>

using namespace std;

// 猴子
class Monkey
{
public:
    Monkey() = default;
    virtual ~Monkey()  = default;

public:
    // 克隆
    virtual Monkey* clone() = 0;
    // 玩耍
    virtual void play() = 0;
};

// 孙悟空
class SunWuKong : public Monkey
{
public:
    SunWuKong(string name);
    SunWuKong(const SunWuKong &other);

public:
    Monkey *clone() override;
    void play() override;

private:
    string _name;
};
