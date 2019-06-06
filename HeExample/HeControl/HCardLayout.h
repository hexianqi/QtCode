/***************************************************************************************************
**      2018-12-13  HCardLayout 卡片布局。
**                  https://blog.csdn.net/liang19890820/article/details/51518841
***************************************************************************************************/

#ifndef HCARDLAYOUT_H
#define HCARDLAYOUT_H

#include "HControlGlobal.h"
#include <QtWidgets/QLayout>

HE_CONTROL_BEGIN_NAMESPACE

class HCardLayoutPrivate;

class HE_CONTROL_EXPORT HCardLayout : public QLayout
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

HE_CONTROL_END_NAMESPACE

#endif // HCARDLAYOUT_H
