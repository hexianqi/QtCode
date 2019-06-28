/***************************************************************************************************
**      2019-06-24  HSlideNavigation 滑动导航
***************************************************************************************************/

#ifndef HSLIDENAVIGATION_H
#define HSLIDENAVIGATION_H

#include "HControlGlobal.h"
#include <QtWidgets/QWidget>
#include <QComboBox>

HE_CONTROL_BEGIN_NAMESPACE

class HSlideNavigationPrivate;

class HSlideNavigation : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(int currentIndex READ currentIndex WRITE setCurrentIndex)
    Q_PROPERTY(bool keyMoveEnable READ isKeyMoveEnable WRITE setKeyMoveEnable)
    Q_PROPERTY(Qt::Orientation orientation READ orientation WRITE setOrientation)
    Q_PROPERTY(bool fixed READ isFixed WRITE setFixed)
    Q_PROPERTY(int space READ space WRITE setSpace)
    Q_PROPERTY(int barRadious READ barRadious WRITE setBarRadious)
    Q_PROPERTY(QColor barBackgroundStart READ barBackgroundStart WRITE setBarBackgroundStart)
    Q_PROPERTY(QColor barBackgroundEnd READ barBackgroundEnd WRITE setBarBackgroundEnd)
    Q_PROPERTY(int itemRadious READ itemRadious WRITE setItemRadious)
    Q_PROPERTY(QColor itemBackgroundStart READ itemBackgroundStart WRITE setItemBackgroundStart)
    Q_PROPERTY(QColor itemBackgroundEnd READ itemBackgroundEnd WRITE setItemBackgroundEnd)
    Q_PROPERTY(QColor itemTextColor READ itemTextColor WRITE setItemTextColor)
    Q_PROPERTY(ItemLineStyle itemLineStyle READ itemLineStyle WRITE setItemLineStyle)
    Q_PROPERTY(int itemLineWidth READ itemLineWidth WRITE setItemLineWidth)
    Q_PROPERTY(QColor itemLineColor READ itemLineColor WRITE setItemLineColor)

public:
    enum ItemLineStyle
    {
        None,       //不显示
        ItemTop,    //上方
        ItemRight,  //右方
        ItemBottom, //下方
        ItemLeft,   //左方
        ItemRect,   //矩形
    };

public:
    explicit HSlideNavigation(QWidget *parent = nullptr);
    ~HSlideNavigation() override;

signals:
    void itemClicked(int index, QString text);

public:
    QStringList items() const;
    int currentIndex() const;
    bool isKeyMoveEnable() const;
    Qt::Orientation orientation() const;
    bool isFixed() const;
    int space() const;
    int barRadious() const;
    QColor barBackgroundStart() const;
    QColor barBackgroundEnd() const;
    int itemRadious() const;
    QColor itemBackgroundStart() const;
    QColor itemBackgroundEnd() const;
    QColor itemTextColor() const;
    ItemLineStyle itemLineStyle() const;
    int itemLineWidth() const;
    QColor itemLineColor() const;

public slots:
    void addItem(QString value);
    void addItem(QStringList value);
    void setCurrentIndex(int value);
    void setKeyMoveEnable(bool b);
    void setOrientation(Qt::Orientation value);
    void setFixed(bool b);
    void setSpace(int value);
    void setBarRadious(int value);
    void setBarBackgroundStart(const QColor &value);
    void setBarBackgroundEnd(const QColor &value);
    void setItemRadious(int value);
    void setItemBackgroundStart(const QColor &value);
    void setItemBackgroundEnd(const QColor &value);
    void setItemTextColor(const QColor &value);
    void setItemLineStyle(ItemLineStyle value);
    void setItemLineWidth(int value);
    void setItemLineColor(const QColor &value);

public slots:
    void moveToFirst();
    void moveToLast();
    void moveToPrevious();
    void moveToNext();
    void moveTo(int value);
    void moveTo(QString value);
    void moveTo(QPointF value);

protected:
    HSlideNavigation(HSlideNavigationPrivate &p, QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *) override;
    void resizeEvent(QResizeEvent *) override;
    void mousePressEvent(QMouseEvent *) override;
    void keyPressEvent(QKeyEvent *) override;
    void drawBarBackground(QPainter *);
    void drawItemBackground(QPainter *);
    void drawItemLine(QPainter *);
    void drawText(QPainter *);
    void adjuseItemSize();

protected slots:
    void doSlide();
    void doShake();

protected:
    QScopedPointer<HSlideNavigationPrivate> d_ptr;

private:
    void init();
};

HE_CONTROL_END_NAMESPACE

#endif // HSLIDENAVIGATION_H
