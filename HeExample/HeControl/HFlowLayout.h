/***************************************************************************************************
**      2018-12-13  HFlowLayout 流布局。
**                  https://blog.csdn.net/liang19890820/article/details/51519015
***************************************************************************************************/

#pragma once

#include "HNamespace.h"
#include <QtWidgets/QLayout>
#include <QtWidgets/QStyle>

HE_BEGIN_NAMESPACE

class HFlowLayoutPrivate;

class HFlowLayout : public QLayout
{
public:
    explicit HFlowLayout(QWidget *parent, int margin = -1, int horizontalSpacing = -1, int verticalSpacing = -1);
    explicit HFlowLayout();
    ~HFlowLayout() override;

public:
    int count() const override;
    void addItem(QLayoutItem *) override;
    QLayoutItem *itemAt(int index) const override;
    QLayoutItem *takeAt(int index) override;
    QSize sizeHint() const override;
    QSize minimumSize() const override;
    Qt::Orientations expandingDirections() const override;
    void setGeometry(const QRect &rect) override;
    bool hasHeightForWidth() const override;
    int heightForWidth(int) const override;

public:
    int horizontalSpacing() const;
    int verticalSpacing() const;
    void setHorizontalSpacing(int);
    void setVerticalSpacing(int);
    void addWidget(QWidget *widget);

protected:
    HFlowLayout(HFlowLayoutPrivate &p, QWidget *parent);

protected:
    int doLayout(const QRect &rect, bool testOnly) const;
    int smartSpacing(QStyle::PixelMetric pm) const;

private:
    QScopedPointer<HFlowLayoutPrivate> d_ptr;
};

HE_END_NAMESPACE
