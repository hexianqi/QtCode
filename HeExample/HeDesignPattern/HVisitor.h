/***************************************************************************************************
**      2019-05-30  访问者模式
**                  https://blog.csdn.net/liang19890820/article/details/79364406
***************************************************************************************************/

#pragma once

#include <list>

using namespace std;

class IVisitor;

// 地方
class IPlace
{
public:
    virtual ~IPlace() = default;

public:
    virtual void accept(IVisitor *) = 0;
};

// 钟楼
class BellTower : public IPlace
{
public:
    void accept(IVisitor *) override;
};

// 兵马俑
class TerracottaWarriors : public IPlace
{
public:
    void accept(IVisitor *) override;
};

// 访问者
class IVisitor
{
public:
    virtual ~IVisitor() = default;

public:
    virtual void visit(BellTower *) = 0;
    virtual void visit(TerracottaWarriors *) = 0;
};

// 游客
class Tourist : public IVisitor
{
public:
    void visit(BellTower *) override;
    void visit(TerracottaWarriors *) override;
};

// 清洁工
class Cleaner : public IVisitor
{
public:
    void visit(BellTower *) override;
    void visit(TerracottaWarriors *) override;
};

// 城市（西安）
class City
{
public:
    void attach(IPlace *);
    void detach(IPlace *);
    void accept(IVisitor *);

private:
    list<IPlace *> _places;
};
