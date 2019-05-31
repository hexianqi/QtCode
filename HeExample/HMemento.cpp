#include "HMemento.h"
#include <iostream>

DateTime::DateTime(string dt) :
    _dateTime(dt)
{

}

void DateTime::setDateTime(string dt)
{
    _dateTime = dt;
}

string DateTime::getDateTime()
{
    return _dateTime;
}

void Life::setDateTime(string dt)
{
    cout << "Set date time to " << dt << endl;
    _dateTime = dt;
}

string Life::getDateTime()
{
    return _dateTime;
}

void Life::setMemento(DateTime *p)
{
    _dateTime = p->getDateTime();
}

DateTime *Life::createMemento()
{
    return new DateTime(_dateTime);
}

PandoraBox::PandoraBox(Life *p) :
    _life(p)
{

}

PandoraBox::~PandoraBox()
{
    for (size_t i = 0; i < _history.size(); i++)
        delete _history.at(i);
    _history.clear();
}

void PandoraBox::save()
{
    cout << "Save ..." << endl;
    _history.push_back(_life->createMemento());
}

void PandoraBox::undo()
{
    cout << "Undo ..." << endl;
    _life->setMemento(_history.back());
    _history.pop_back();
}
