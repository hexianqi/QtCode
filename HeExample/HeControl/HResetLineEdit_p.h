#ifndef HRESETLINEEDIT_P_H
#define HRESETLINEEDIT_P_H

#include "HResetLineEdit.h"
#include "HButtonLineEdit_p.h"

HE_CONTROL_BEGIN_NAMESPACE

class HResetLineEditPrivate : public HButtonLineEditPrivate
{
public:
    QString defaultText;
};

HE_CONTROL_END_NAMESPACE

#endif // HRESETLINEEDIT_P_H
