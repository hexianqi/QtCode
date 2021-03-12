/***************************************************************************************************
**      2020-03-27  HNinePatchPainter 九宫格绘制
**                  https://qtdebug.com/qtbook-paint-nine-patch-painter/
***************************************************************************************************/

#pragma once

#include <QtUiPlugin/QDesignerExportWidget>
#include <QtCore/QScopedPointer>

class QMargins;
class QPixmap;
class QRect;
class QPainter;
class HNinePatchPainterPrivate;

class HNinePatchPainter
{
public:
    explicit HNinePatchPainter();
    virtual ~HNinePatchPainter();

public:
    void setMargins(QMargins value);
    void setMargins(int left, int top, int right, int bottom);
    void setStretchHorizontal(bool b);
    void setStretchVertical(bool b);
    void setBackground(const QPixmap &);

public:
    void draw(QPainter *painter, const QRect &rect);

protected:
    HNinePatchPainter(HNinePatchPainterPrivate &);

protected:
    void rebuildPixmapIfNeeded();

protected:
    QScopedPointer<HNinePatchPainterPrivate> d_ptr;
};
