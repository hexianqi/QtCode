#pragma once

#include <QException>
#include "HErrorType.h"

HE_CORE_BEGIN_NAMESPACE

class HE_CORE_EXPORT HException : public QException
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

HE_CORE_END_NAMESPACE

