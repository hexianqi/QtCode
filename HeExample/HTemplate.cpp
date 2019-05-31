#include "HTemplate.h"
#include <iostream>

using namespace std;

void Company::recruit()
{
    cout << "---------- Begin ----------" << endl;
    careerTalk();
    receiveResume();
    interview();
    offer();
    cout << "---------- End ----------" << endl;
}

void Company::careerTalk()
{
    cout << "Delivery" << endl;
}

void Company::receiveResume()
{
    cout << "Receive Resume" << endl;
}

void Alibaba::interview()
{
    cout << "First interview -> Second interview -> Third interview" << endl;
}

void Alibaba::offer()
{
    cout << "30W" << std::endl;
}

void Tencent::interview()
{
    cout << "First interview -> Second interview" << endl;
}

void Tencent::offer()
{
    cout << "25W" << endl;
}
