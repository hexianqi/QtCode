#pragma once

#include "HGraphicsPixmapItem.h"
#include "HGraphicsObject_p.h"

HE_BEGIN_NAMESPACE

class HGraphicsPixmapItemPrivate : public HGraphicsObjectPrivate
{
public:
    HGraphicsPixmapItemPrivate();

public:
    QPixmap pixmap;
    QString title;
    QColor textColor = Qt::red;
    QString fileName;
    QMovie *movie = nullptr;
};

HE_END_NAMESPACE

