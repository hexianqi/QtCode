#ifndef HCLEARLINEEDIT_P_H
#define HCLEARLINEEDIT_P_H

#include "HClearLineEdit.h"
#include "HButtonLineEdit_p.h"

HE_CONTROL_BEGIN_NAMESPACE

class HClearLineEditPrivate : public HButtonLineEditPrivate
{
public:
    bool vis = false;
};

HE_CONTROL_END_NAMESPACE

#endif // HCLEARLINEEDIT_P_H
