/***************************************************************************************************
**      2022-06-24  HCanvasItem
***************************************************************************************************/

#pragma once

#include <QtCore/QScopedPointer>

class HCanvas;
class HCanvasItemExtra;
class HCanvasItemPrivate;

class HCanvasItem
{
public:
    enum RttiValues
    {
        Rtti_Item = 0,
        Rtti_Sprite = 1,
        Rtti_PolygonalItem = 2,
        Rtti_Text = 3,
        Rtti_Polygon = 4,
        Rtti_Rectangle = 5,
        Rtti_Ellipse = 6,
        Rtti_Line = 7,
        Rtti_Spline = 8
    };

public:
    explicit HCanvasItem();
    virtual ~HCanvasItem();

public:
    double x() const;
    double y() const;
    double z() const;
    bool isAnimated() const;
    double xVelocity() const;
    double yVelocity() const;
    QList<HCanvasItem *> collisions(bool exact) const;

public:
    void move(double x, double y);
    void setX(double);
    void setY(double);
    void setZ(double);
    void setXVelocity(double);
    void setYVelocity(double);

public:
    virtual void setCanvas(HCanvas *);
    virtual void setAnimated(bool);
    virtual void setVelocity(double vx, double vy);
    virtual void moveBy(double dx, double dy);
    virtual void advance(int stage);
    virtual bool collidesWith(const HCanvasItem *) const = 0;





    virtual void draw(QPainter&)=0;

    void show();
    void hide();

    virtual void setVisible(bool yes);
    bool isVisible() const
    { return (bool)vis; }
    virtual void setSelected(bool yes);
    bool isSelected() const
    { return (bool)sel; }
    virtual void setEnabled(bool yes);
    bool isEnabled() const
    { return (bool)ena; }
    virtual void setActive(bool yes);
    bool isActive() const
    { return (bool)act; }
    bool visible() const
    { return (bool)vis; }
    bool selected() const
    { return (bool)sel; }
    bool enabled() const
    { return (bool)ena; }
    bool active() const
    { return (bool)act; }



    virtual int rtti() const;
    static int RTTI;

    virtual QRect boundingRect() const=0;
    virtual QRect boundingRectAdvanced() const;

    QtCanvas* canvas() const
    { return cnv; }

protected:
    void update() { changeChunks(); }

private:
    // For friendly subclasses...

    friend class QtCanvasPolygonalItem;
    friend class QtCanvasSprite;
    friend class QtCanvasRectangle;
    friend class QtCanvasPolygon;
    friend class QtCanvasEllipse;
    friend class QtCanvasText;
    friend class QtCanvasLine;

    virtual QPolygon chunks() const;
    virtual void addToChunks();
    virtual void removeFromChunks();
    virtual void changeChunks();
    virtual bool collidesWith(const QtCanvasSprite*,
                              const QtCanvasPolygonalItem*,
                              const QtCanvasRectangle*,
                              const QtCanvasEllipse*,
                              const QtCanvasText*) const = 0;

protected:
    HCanvasItem(HCanvasItemPrivate &);

protected:
    QScopedPointer<HCanvasItemPrivate> d_ptr;
};



