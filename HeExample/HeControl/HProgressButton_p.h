#pragma once

#include "HProgressButton.h"

class QVariantAnimation;

HE_BEGIN_NAMESPACE

class HProgressButtonPrivate
{
public:
    HProgressButton::State buttonState = HProgressButton::Normal;
    QString text = "我是按钮";
    QTimer *timer;
    int widthChangeValue = 0;
    int progress = 0;
};

class HWaterDrop : public QWidget
{
    Q_OBJECT

public:
    HWaterDrop(QWidget *parent = nullptr);

public:
    void show();
    void move(const QPoint &point);

private:
    void paintEvent(QPaintEvent *);
    void onRaduisChanged(QVariant value);

private:
    QVariantAnimation *_waterDropAnimation;
    int _animationRadius = 0;
};
HE_END_NAMESPACE

