#ifndef HRICHTEXTBUTTON_P_H
#define HRICHTEXTBUTTON_P_H

#include "HRichTextButton.h"

HE_CONTROL_BEGIN_NAMESPACE

class HRichTextButtonPrivate
{
public:
    QTextDocument *doc = nullptr;
    bool internalDoc = false;
};

HE_CONTROL_END_NAMESPACE

#endif // HRICHTEXTBUTTON_P_H
