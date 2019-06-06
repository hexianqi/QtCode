#include "HState.h"
#include <iostream>

using namespace std;

RedLight::RedLight(TrafficLights *p) :
    _context(p)
{

}

void RedLight::handle()
{
    cout << "Red Light" << endl;
    _context->setState(new GreenLight(_context));
    delete this;
}

// 绿灯
GreenLight::GreenLight(TrafficLights *p) :
    _context(p)
{

}

void GreenLight::handle()
{
    cout << "Green Light" << endl;
    _context->setState(new YellowLight(_context));
    delete this;
}

YellowLight::YellowLight(TrafficLights *p) :
    _context(p)
{

}

void YellowLight::handle()
{
    cout << "Yellow Light" << endl;
    _context->setState(new RedLight(_context));
    delete this;
}

TrafficLights::TrafficLights()
{
    _state = new RedLight(this);
}

void TrafficLights::setState(IState *p)
{
    _state = p;
}

void TrafficLights::request()
{
    _state->handle();
}
