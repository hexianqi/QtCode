#pragma once

#include "HBinaryTreeWidget.h"

HE_BEGIN_NAMESPACE

struct HBinaryTreeNode
{
    QChar data;
    HBinaryTreeNode *lchild = nullptr;
    HBinaryTreeNode *rchild = nullptr;
};

class HBinaryTreeWidgetPrivate
{
public:
    HBinaryTreeNode *root = nullptr;
};

HE_END_NAMESPACE

