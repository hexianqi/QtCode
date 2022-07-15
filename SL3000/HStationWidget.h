/***************************************************************************************************
**      2022-07-14  HStationWidget
***************************************************************************************************/

#pragma once

#include <QtWidgets/QWidget>

class HStationWidgetPrivate;

class HStationWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HStationWidget(int index, QWidget *parent = nullptr);
    ~HStationWidget() override;

protected:
    void initialize(int index);


protected:
    QScopedPointer<HStationWidgetPrivate> d_ptr;
};



