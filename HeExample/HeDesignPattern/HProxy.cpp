#include "HProxy.h"
#include <iostream>

using namespace std;

void CMCC::recharge(int money)
{
    cout << "Recharge " << money;
}

Proxy::Proxy()
{
    _CMCC = nullptr;
}

Proxy::~Proxy()
{
    delete _CMCC;
}

void Proxy::recharge(int money)
{
    if (money >= 50)
    {
        if (_CMCC == nullptr)
            _CMCC = new CMCC();
        _CMCC->recharge(money);
    }
    else
        cout << "Sorry, too little money" << endl;
}
