#include "HBuilder.h"

void Computer::setCpu(string value)
{
    _cpu = value;
}

void Computer::setMainboard(string value)
{
    _mainboard = value;
}

void Computer::setRam(string value)
{
    _ram = value;
}

void Computer::setVideoCard(string value)
{
    _videoCard = value;
}

string Computer::getCPU()
{
    return _cpu;
}

string Computer::getMainboard()
{
    return _mainboard;
}

string Computer::getRam()
{
    return _ram;
}

string Computer::getVideoCard()
{
    return _videoCard;
}

ThinkPadBuilder::ThinkPadBuilder()
{
    _computer = new Computer();
}

void ThinkPadBuilder::buildCpu()
{
    _computer->setCpu("i5-6200U");
}

void ThinkPadBuilder::buildMainboard()
{
    _computer->setMainboard("Intel DH57DD");
}

void ThinkPadBuilder::buildRam()
{
    _computer->setRam("DDR4");
}

void ThinkPadBuilder::buildVideoCard()
{
    _computer->setVideoCard("NVIDIA Geforce 920MX");
}

Computer *ThinkPadBuilder::getResult()
{
    return _computer;
}

YogaBuilder::YogaBuilder()
{
    _computer = new Computer();
}

void YogaBuilder::buildCpu()
{
    _computer->setCpu("i7-7500U");
}

void YogaBuilder::buildMainboard()
{
    _computer->setMainboard("Intel DP55KG");
}

void YogaBuilder::buildRam()
{
    _computer->setRam("DDR5");
}

void YogaBuilder::buildVideoCard()
{
    _computer->setVideoCard("NVIDIA GeForce 940MX");
}

Computer *YogaBuilder::getResult()
{
    return _computer;
}

void Direcror::create(IBuilder *builder)
{
    builder->buildCpu();
    builder->buildMainboard();
    builder->buildRam();
    builder->buildVideoCard();
}
