/***************************************************************************************************
**      2018-12-14  HBorderLayout 边框布局。
**                  https://blog.csdn.net/liang19890820/article/details/51519088
***************************************************************************************************/

#ifndef HBORDERLAYOUT_H
#define HBORDERLAYOUT_H

#include "HExampleGlobal.h"
#include <QLayout>

HE_EXAMPLE_BEGIN_NAMESPACE

class HBorderLayoutPrivate;

class HE_EXAMPLE_EXPORT HBorderLayout : public QLayout
{
public:
    enum Position { West, North, South, East, Center };
    enum SizeType { MinimumSize, SizeHint };

public:
    explicit HBorderLayout(QWidget *parent, int margin = 0, int spacing = -1);
    explicit HBorderLayout();
    virtual ~HBorderLayout();


public:
    virtual int count() const override;
    virtual void addItem(QLayoutItem *) override;
    virtual QLayoutItem *itemAt(int index) const override;
    virtual QLayoutItem *takeAt(int index) override;
    virtual QSize sizeHint() const override;
    virtual QSize minimumSize() const override;
    virtual Qt::Orientations expandingDirections() const override;
    virtual void setGeometry(const QRect &rect) override;

public:
    void add(QLayoutItem *item, Position position);
    void add(QWidget *widget, Position position);

protected:
    HBorderLayout(HBorderLayoutPrivate &p, QWidget *parent);

protected:
    QSize calculateSize(SizeType sizeType) const;

private:
    QScopedPointer<HBorderLayoutPrivate> d_ptr;
};

HE_EXAMPLE_END_NAMESPACE

#endif // HBORDERLAYOUT_H
