#pragma once

#include "HIconFontHelper.h"
#include <QtGui/QFont>

HE_BEGIN_NAMESPACE

class IIconFontFactory;

class HIconFontHelperPrivate
{
public:
    QFont font;
    QString family;
    IIconFontFactory *factory = nullptr;

public:
    QList<QAbstractButton *> btns;  // 按钮队列
    QList<QPixmap> pixNormal;       // 正常图片队列
    QList<QPixmap> pixHover;        // 悬停图片队列
    QList<QPixmap> pixPressed;      // 按下图片队列
    QList<QPixmap> pixChecked;      // 选中图片队列
};

HE_END_NAMESPACE
