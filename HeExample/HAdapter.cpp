#include "HAdapter.h"
#include "HDesignPattern.h"
#include <iostream>

using namespace std;

void OwnCharger::chargeWithFeetFlat()
{
    cout << "OwnCharger::chargeWithFeetFlat" << endl;
}

PowerAdapter::PowerAdapter()
{
    _charger = new OwnCharger;
}

PowerAdapter::~PowerAdapter()
{
    SAFE_DELETE(_charger);
}

void PowerAdapter::charge()
{
    //  使用自带的充电器（两脚扁型）充电
    _charger->chargeWithFeetFlat();
}
