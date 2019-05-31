#include "HCommand.h"
#include <iostream>

void Reciever::takeOrder()
{
    cout << "Take order..." << endl;
}

void Reciever::receipt()
{
    cout << "Receipt..." << endl;
}

Command::Command(Reciever *p)
{
    _reciever = p;
}

TakeCommand::TakeCommand(Reciever *p) :
    Command(p)
{
}

void TakeCommand::execute()
{
    cout << "Take command..." << endl;
    _reciever->takeOrder();
}

PayCommand::PayCommand(Reciever *p) :
    Command(p)
{

}

void PayCommand::execute()
{
    cout << "Pay command..." << endl;
    _reciever->receipt();
}

Invoker::Invoker()
{
}

void Invoker::addCmd(Command *p)
{
    _cmds.push_back(p);
}

void Invoker::deleteCmd(Command *p)
{
    _cmds.remove(p);
}

void Invoker::notify()
{
    for (auto it = _cmds.begin(); it != _cmds.end(); it++)
        (*it)->execute();
}
