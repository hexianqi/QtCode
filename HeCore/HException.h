#pragma once

#include "HErrorType.h"
#include <QException>

HE_BEGIN_NAMESPACE

class HException : public QException
{
public:
    HException(HErrorType);
    HException(QString);

public:
    void raise() const override;
    HException *clone() const override;
    QString message();

private:
    HErrorType _type;
    QString _message;
};

HE_END_NAMESPACE

