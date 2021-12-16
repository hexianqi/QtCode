#pragma once

#include "HRichTextButton.h"

HE_BEGIN_NAMESPACE

class HRichTextButtonPrivate
{
public:
    QTextDocument *doc = nullptr;
    bool internalDoc = false;
};

HE_END_NAMESPACE
