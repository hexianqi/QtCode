#pragma once

#include "HGraphicsNoteItem.h"
#include "HGraphicsObject_p.h"

HE_BEGIN_NAMESPACE

class HGraphicsNoteItemPrivate : public HGraphicsObjectPrivate
{
public:
    HGraphicsNoteItemPrivate();

public:
    QString title;
    QStringList content;
    int showContentIndex = 0;
    int pressButtonIndex = -1;
    int pressTextIndex = -1;
    int currentPage = 0;
    int currentPaintSize = 0;
    int fullPage = 0;
    QVector<QRectF> buttonRects;
    QVector<QRectF> textRects;
};

HE_END_NAMESPACE

