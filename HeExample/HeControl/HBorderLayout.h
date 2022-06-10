/***************************************************************************************************
**      2018-12-14  HBorderLayout 边框布局。
**                  https://blog.csdn.net/liang19890820/article/details/51519088
***************************************************************************************************/

#pragma once

#include "HNamespace.h"
#include <QtWidgets/QLayout>

HE_BEGIN_NAMESPACE

class HBorderLayoutPrivate;

class HBorderLayout : public QLayout
{
public:
    enum Position { West, North, South, East, Center };
    enum SizeType { MinimumSize, SizeHint };

public:
    explicit HBorderLayout(QWidget *parent, int margin = 0, int spacing = -1);
    explicit HBorderLayout();
    ~HBorderLayout() override;

public:
    int count() const override;
    void addItem(QLayoutItem *) override;
    QLayoutItem *itemAt(int index) const override;
    QLayoutItem *takeAt(int index) override;
    QSize sizeHint() const override;
    QSize minimumSize() const override;
    Qt::Orientations expandingDirections() const override;
    void setGeometry(const QRect &rect) override;

public:
    void addItem(QLayoutItem *item, Position position);
    void addWidget(QWidget *widget, Position position);

protected:
    HBorderLayout(HBorderLayoutPrivate &p, QWidget *parent);

protected:
    QSize calcSize(SizeType) const;

private:
    QScopedPointer<HBorderLayoutPrivate> d_ptr;
};

HE_END_NAMESPACE
