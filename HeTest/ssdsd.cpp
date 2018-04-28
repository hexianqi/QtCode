#include "ssdsd.h"

class ssdsdData : public QSharedData
{
public:

};

ssdsd::ssdsd() : data(new ssdsdData)
{
}

ssdsd::ssdsd(const ssdsd &rhs) : data(rhs.data)
{

}

ssdsd &ssdsd::operator=(const ssdsd &rhs)
{
    if (this != &rhs)
        data.operator=(rhs.data);
    return *this;
}

ssdsd::~ssdsd()
{

}
