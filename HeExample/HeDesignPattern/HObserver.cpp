#include "HObserver.h"
#include <iostream>

ConcreteObserver::ConcreteObserver(string name)
{
    _name = name;
}

void ConcreteObserver::update(float price)
{
    cout << _name << " - price: " << price << "\n";
}

ConcreteSubject::ConcreteSubject()
{
    _price = 10.0;
}

void ConcreteSubject::setPrice(float value)
{
    _price = value;
}

void ConcreteSubject::attach(IObserver *p)
{
    _observers.push_back(p);
}

void ConcreteSubject::detach(IObserver *p)
{
    _observers.remove(p);
}

void ConcreteSubject::notify()
{
    for (auto it = _observers.begin(); it != _observers.end(); it++)
        (*it)->update(_price);
}

