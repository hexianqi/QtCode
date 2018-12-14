/***************************************************************************************************
**      2018-12-13  HFlowLayout 流布局。
**                  https://blog.csdn.net/liang19890820/article/details/51519015
***************************************************************************************************/

#ifndef HFLOWLAYOUT_H
#define HFLOWLAYOUT_H

#include "HExampleGlobal.h"
#include <QLayout>
#include <QStyle>

HE_EXAMPLE_BEGIN_NAMESPACE

class HFlowLayoutPrivate;

class HE_EXAMPLE_EXPORT HFlowLayout : public QLayout
{
public:
    explicit HFlowLayout(QWidget *parent, int margin = -1, int hSpacing = -1, int vSpacing = -1);
    explicit HFlowLayout();
    virtual ~HFlowLayout();

public:
    virtual int count() const override;
    virtual void addItem(QLayoutItem *) override;
    virtual QLayoutItem *itemAt(int index) const override;
    virtual QLayoutItem *takeAt(int index) override;
    virtual QSize sizeHint() const override;
    virtual QSize minimumSize() const override;
    virtual Qt::Orientations expandingDirections() const override;
    virtual void setGeometry(const QRect &rect) override;
    virtual bool hasHeightForWidth() const override;
    virtual int heightForWidth(int) const override;

public:
    int horizontalSpacing() const;
    int verticalSpacing() const;

protected:
    HFlowLayout(HFlowLayoutPrivate &p, QWidget *parent);

protected:
    int doLayout(const QRect &rect, bool testOnly) const;
    int smartSpacing(QStyle::PixelMetric pm) const;

private:
    QScopedPointer<HFlowLayoutPrivate> d_ptr;
};

HE_EXAMPLE_END_NAMESPACE

#endif // HFLOWLAYOUT_H
