/***************************************************************************************************
**      2018-12-13  HCardLayout 卡片布局。
**                  https://blog.csdn.net/liang19890820/article/details/51518841
***************************************************************************************************/

#pragma once

#include "HNamespace.h"
#include <QtWidgets/QLayout>

HE_BEGIN_NAMESPACE

class HCardLayoutPrivate;

class HCardLayout : public QLayout
{
public:
    explicit HCardLayout(QWidget *parent);
    explicit HCardLayout();
    ~HCardLayout() override;

public:
    int count() const override;
    void addItem(QLayoutItem *) override;
    QLayoutItem *itemAt(int index) const override;
    QLayoutItem *takeAt(int index) override;
    QSize sizeHint() const override;
    QSize minimumSize() const override;
    void setGeometry(const QRect &rect) override;

protected:
    HCardLayout(HCardLayoutPrivate &p, QWidget *parent);

private:
    QScopedPointer<HCardLayoutPrivate> d_ptr;
};

HE_END_NAMESPACE
