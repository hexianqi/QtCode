#include "HChain.h"
#include <iostream>

using namespace std;

IHandler::IHandler()
{
    _successor = nullptr;
}

void IHandler::setSuccessor(IHandler *p)
{
    _successor = p;
}

void Manager::handleRequest(float days)
{
    if (days <= 1)
        cout << "Manager 批准了 " << days << " 天假" << endl;
    else
        _successor->handleRequest(days);
}

void Director::handleRequest(float days)
{
    if (days <= 3)
        cout << "Director 批准了 " << days << " 天假" << endl;
    else
        _successor->handleRequest(days);
}

void CEO::handleRequest(float days)
{
    if (days <= 7)
        cout << "CEO 批准了 " << days << " 天假" << endl;
    else
        cout << "给你放长假，以后不用来上班啦！" << endl;
}
