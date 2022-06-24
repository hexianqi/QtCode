/***************************************************************************************************
**      2022-06-20  HSimpleWidget
***************************************************************************************************/

#pragma once

#include <QtWidgets/QWidget>

class HVariantWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HVariantWidget(QWidget *parent = nullptr);
    ~HVariantWidget() override;

protected:
    void init();
};



