/***************************************************************************************************
**      2018-12-13  HCardLayout 卡片布局。
**                  https://blog.csdn.net/liang19890820/article/details/51518841
***************************************************************************************************/

#ifndef HCARDLAYOUT_H
#define HCARDLAYOUT_H

#include "HExampleGlobal.h"
#include <QLayout>

HE_EXAMPLE_BEGIN_NAMESPACE

class HCardLayoutPrivate;

class HE_EXAMPLE_EXPORT HCardLayout : public QLayout
{
public:
    explicit HCardLayout(QWidget *parent);
    explicit HCardLayout();
    virtual ~HCardLayout();

public:
    virtual int count() const override;
    virtual void addItem(QLayoutItem *) override;
    virtual QLayoutItem *itemAt(int index) const override;
    virtual QLayoutItem *takeAt(int index) override;
    virtual QSize sizeHint() const override;
    virtual QSize minimumSize() const override;
    virtual void setGeometry(const QRect &rect) override;

protected:
    HCardLayout(HCardLayoutPrivate &p, QWidget *parent);

private:
    QScopedPointer<HCardLayoutPrivate> d_ptr;
};

HE_EXAMPLE_END_NAMESPACE

#endif // HCARDLAYOUT_H
