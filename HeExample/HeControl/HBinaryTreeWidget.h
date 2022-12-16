/***************************************************************************************************
**      2022-12-13  HBinaryTreeWidget
***************************************************************************************************/

#pragma once

#include "HNamespace.h"
#include <QtWidgets/QWidget>

HE_BEGIN_NAMESPACE

class HBinaryTreeWidgetPrivate;

class HBinaryTreeWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HBinaryTreeWidget(QWidget *parent = nullptr);
    ~HBinaryTreeWidget() override;

public:
    void setBinaryTree(const QString &);

protected:
    void paintEvent(QPaintEvent *)override;

protected:
    QScopedPointer<HBinaryTreeWidgetPrivate> d_ptr;
};

HE_END_NAMESPACE

