/***************************************************************************************************
**      2022-02-14  HLocationWidget
***************************************************************************************************/

#pragma once

#include <QtWidgets/QWidget>

class HLocationWidgetPrivate;

class HLocationWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HLocationWidget(QWidget *parent = nullptr);
    ~HLocationWidget() override;

public:
    void setPolygon(const QPolygon &);
    void setColor(const QColor &invalid, const QColor &spacer);
    void clearResult();
    void refreshResult();

protected:
    void init();
    void resetLayout();


protected:
    QScopedPointer<HLocationWidgetPrivate> d_ptr;
};



