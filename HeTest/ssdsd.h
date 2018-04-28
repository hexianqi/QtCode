#ifndef SSDSD_H
#define SSDSD_H

#include <QSharedDataPointer>

class ssdsdData;

class ssdsd
{
public:
    ssdsd();
    ssdsd(const ssdsd &);
    ssdsd &operator=(const ssdsd &);
    ~ssdsd();

private:
    QSharedDataPointer<ssdsdData> data;
};

#endif // SSDSD_H