#include "HMediator.h"
#include <iostream>

void IMediator::registerColleague(IColleague *p)
{
    _colleagues.emplace_back(p);
}

const list<IColleague *> &IMediator::getColleagues() const
{
    return _colleagues;
}

void ConcreteMediator::distributeMessage(const IColleague *sender, const string &message) const
{
    for (auto c : getColleagues())
    {
        // 不要将消息发送给自己
        if (c != sender)
            c->receiveMessage(sender, message);
    }
}

IColleague::IColleague(const string &name) :
    _name (name)
{

}

string IColleague::getName() const
{
    return _name;
}

void ConcreteColleague::sendMessage(const IMediator &mediator, const string &message) const
{
    mediator.distributeMessage(this, message);
}

void ConcreteColleague::receiveMessage(const IColleague *sender, const string &message) const
{
    cout << getName() << " received the message from "
         << sender->getName() << ": " << message << endl;
}
