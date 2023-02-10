/***************************************************************************************************
**      2022-12-28  HProgressButton
***************************************************************************************************/

#pragma once

#include "HNamespace.h"
#include <QtWidgets/QWidget>

HE_BEGIN_NAMESPACE

class HProgressButtonPrivate;

class HProgressButton : public QWidget
{
    Q_OBJECT

public:
    enum State
    {
        Normal,
        Hover,
        Corner,
        OpenProgress,
        CloseProgress,
        Recovery
    };

public:
    explicit HProgressButton(QWidget *parent = nullptr);
    ~HProgressButton() override;

signals:
    void startProcessing();

protected:
    void paintEvent(QPaintEvent *) override;
    void enterEvent(QEvent *) override;
    void leaveEvent(QEvent *) override;
    void mousePressEvent(QMouseEvent *) override;
    void onTimeout();
    void operationProcessing();

protected:
    QScopedPointer<HProgressButtonPrivate> d_ptr;
};

HE_END_NAMESPACE

