#ifndef TWST_H
#define TWST_H

#include <QtCore/QSharedDataPointer>

class TwstData;

class Twst
{
public:
    Twst();
    Twst(const Twst &);
    Twst &operator=(const Twst &);
    ~Twst();

    Twst *clone();

private:
    QSharedDataPointer<TwstData> data;
};

#endif // TWST_H
