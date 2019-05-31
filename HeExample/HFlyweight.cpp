#include "HFlyweight.h"
#include <iostream>

map<string, IPlayer *> PlayerFactory::__map = map<string, IPlayer *>();

Terrorist::Terrorist()
{
    _task = "Plant a bomb";
}

void Terrorist::assignWeapon(string weapon)
{
    _weapon = weapon;
}

void Terrorist::mission()
{
    cout << "Terrorist with weapon " + _weapon + "," + " Task is " + _task << endl;
}

CounterTerrorist::CounterTerrorist()
{
    _task = "Diffuse bomb";
}

void CounterTerrorist::assignWeapon(string weapon)
{
    _weapon = weapon;
}

void CounterTerrorist::mission()
{
    cout << "Counter Terrorist with weapon " + _weapon + "," + " Task is " + _task << endl;
}

IPlayer *PlayerFactory::getPlayer(string type)
{
    if (__map.find(type) != __map.end())
        return __map[type];

    IPlayer *p = nullptr;
    if (type == "T")
    {
        cout << "Terrorist Created" << endl;
        p = new Terrorist();
    }
    else if (type == "CT")
    {
        cout << "Counter Terrorist Created" << endl;
        p = new CounterTerrorist();
    }
    else
    {
        cout << "Unreachable code!" << endl;
    }
    __map.insert(make_pair(type, p));
    return p;
}
