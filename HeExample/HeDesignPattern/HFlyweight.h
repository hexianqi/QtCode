/***************************************************************************************************
**      2019-05-30  享元模式
**                  https://blog.csdn.net/liang19890820/article/details/79629690
***************************************************************************************************/

#pragma once

#include <string>
#include <map>

using namespace std;

// 玩家类型和武器
static string __playerType[2] = { "T", "CT" };
static string __weapons[4] = { "AK-47", "Maverick", "Gut Knife", "Desert Eagle" };

// 玩家 - 有武器和使命
class IPlayer
{
public:
    virtual ~IPlayer() = default;

public:
    // 分配武器
    virtual void assignWeapon(string weapon) = 0;
    // 使命
    virtual void mission() = 0;

protected:
    string _task;   // 内部状态
    string _weapon; // 外部状态
};

// 恐怖分子
class Terrorist : public IPlayer
{
public:
    Terrorist();

public:
    void assignWeapon(string weapon) override;
    void mission() override;
};

// 反恐精英
class CounterTerrorist : public IPlayer
{
public:
    CounterTerrorist();

public:
    void assignWeapon(string weapon) override;
    void mission() override;
};

// 玩家工厂
class PlayerFactory
{
public:
    // 如果 T/CT 对象存在，则直接从享元池获取；否则，创建一个新对象并添加到享元池中，然后返回。
    static IPlayer *getPlayer(string type);

private:
    // 存储 T/CT 对象（享元池）
    static map<string, IPlayer *> __map;
};
