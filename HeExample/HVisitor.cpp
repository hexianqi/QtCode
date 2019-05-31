#include "HVisitor.h"
#include <iostream>

void BellTower::accept(IVisitor *p)
{
    cout << "Bell Tower is accepting visitor." << endl;
    p->visit(this);
}

void TerracottaWarriors::accept(IVisitor *p)
{
    cout << "Terracotta Warriors is accepting visitor." << endl;
    p->visit(this);
}

void Tourist::visit(BellTower *)
{
    cout << "I'm visiting the Bell Tower!" << endl;
}

void Tourist::visit(TerracottaWarriors *)
{
    cout << "I'm visiting the Terracotta Warriors!" << endl;
}

void Cleaner::visit(BellTower *)
{
    cout << "I'm cleaning up the garbage of Bell Tower!" << endl;
}

void Cleaner::visit(TerracottaWarriors *)
{
    cout << "I'm cleaning up the garbage of Terracotta Warriors!" << endl;
}

void City::attach(IPlace *p)
{
    _places.push_back(p);
}

void City::detach(IPlace *p)
{
    _places.remove(p);
}

void City::accept(IVisitor *p)
{
    // 为每一个 element 设置 visitor，进行对应的操作
    for (auto it = _places.begin(); it != _places.end(); ++it)
        (*it)->accept(p);
}
