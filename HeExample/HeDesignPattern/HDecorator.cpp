#include "HDecorator.h"

string HouseBlend::name()
{
    return "HouseBlend";
}

double HouseBlend::cost()
{
    return 30.0;
}

string DarkRoast::name()
{
    return "DarkRoast";
}

double DarkRoast::cost()
{
    return 28.5;
}

CondimentDecorator::CondimentDecorator(IBeverage *p)
{
    _beverage = p;
}

string CondimentDecorator::name()
{
    return _beverage->name();
}

double CondimentDecorator::cost()
{
    return _beverage->cost();
}

Cream::Cream(IBeverage *p) :
    CondimentDecorator(p)
{

}

string Cream::name()
{
    return _beverage->name() + " Cream";
}

double Cream::cost()
{
    return _beverage->cost() + 3.5;
}

Mocha::Mocha(IBeverage *p) :
    CondimentDecorator(p)
{
}

string Mocha::name()
{
    return _beverage->name() + " Mocha";
}

double Mocha::cost()
{
    return _beverage->cost() + 2.0;
}

Syrup::Syrup(IBeverage *p) :
    CondimentDecorator(p)
{
}

string Syrup::name()
{
    return _beverage->name() + " Syrup";
}

double Syrup::cost()
{
    return _beverage->cost() + 3.0;
}
