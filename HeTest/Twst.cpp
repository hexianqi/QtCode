#include "Twst.h"

class TwstData : public QSharedData
{
public:

};

Twst::Twst() : data(new TwstData)
{

}

Twst::Twst(const Twst &rhs) : data(rhs.data)
{

}

Twst &Twst::operator=(const Twst &rhs)
{
    if (this != &rhs)
        data.operator=(rhs.data);
    return *this;
}

Twst::~Twst()
{

}

Twst *Twst::clone()
{
    return new Twst(*this);
}
