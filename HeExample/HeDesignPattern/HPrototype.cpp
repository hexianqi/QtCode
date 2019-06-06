#include "HPrototype.h"
#include <iostream>

SunWuKong::SunWuKong(string name)
{
    _name = name;
}

SunWuKong::SunWuKong(const SunWuKong &other)
{
    _name = other._name;
}

Monkey *SunWuKong::clone()
{
    return new SunWuKong(*this);
}

void SunWuKong::play()
{
    cout << _name << " play Golden-Hoop-Stick" << endl;
}
