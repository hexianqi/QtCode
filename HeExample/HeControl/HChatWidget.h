/***************************************************************************************************
**      2022-11-03  HChatWidget
***************************************************************************************************/

#pragma once

#include "HNamespace.h"
#include <QtWidgets/QWidget>

HE_BEGIN_NAMESPACE

class HChatWidgetPrivate;

class HChatWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HChatWidget(QWidget *parent = nullptr);
    ~HChatWidget() override;

public:
    void setUserName(QString);
    void addPixmap(QString userName, QPixmap pixmap);
    void addPixmap(QString userName, QString fileName);
    void addChart(QString userName, QString message);

protected:
    HChatWidget(HChatWidgetPrivate &p, QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *)override;

protected:
    QScopedPointer<HChatWidgetPrivate> d_ptr;
};

HE_END_NAMESPACE
