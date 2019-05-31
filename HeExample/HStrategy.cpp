#include "HStrategy.h"
#include <iostream>

using namespace std;

void BikeStrategy::travel()
{
    cout << "Travel by bike" << endl;
}

void CarStrategy::travel()
{
    cout << "Travel by car" << endl;
}

void TrainStrategy::travel()
{
    cout << "Travel by train" << endl;
}

Context::Context(IStrategy *p)
{
    _strategy = p;
}

void Context::travel()
{
    _strategy->travel();
}
