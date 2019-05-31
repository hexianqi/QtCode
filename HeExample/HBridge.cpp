#include "HBridge.h"
#include <iostream>

using namespace std;

void Light::powerOn()
{
    cout << "Light is on." << endl;
}

void Light::powerOff()
{
    cout << "Light is off." << endl;
}

void Fan::powerOn()
{
    cout << "Fan is on." << endl;
}

void Fan::powerOff()
{
    cout << "Fan is off." << endl;
}

ISwitch::ISwitch(IElectricalEquipment *p)
{
    _ee = p;
}

PullChainSwitch::PullChainSwitch(IElectricalEquipment *p) :
    ISwitch(p)
{

}

void PullChainSwitch::on()
{
    cout << "Switch on the equipment with a pull chain switch." << endl;
    _ee->powerOn();
}

void PullChainSwitch::off()
{
    cout << "Switch off the equipment with a pull chain switch." << endl;
    _ee->powerOff();
}

TwoPositionSwitch::TwoPositionSwitch(IElectricalEquipment *p) :
    ISwitch(p)
{

}

void TwoPositionSwitch::on()
{
    cout << "Switch on the equipment with a two-position switch." << endl;
    _ee->powerOn();
}

void TwoPositionSwitch::off()
{
    cout << "Switch off the equipment with a two-position switch." << endl;
    _ee->powerOff();
}
