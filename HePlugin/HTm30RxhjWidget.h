/***************************************************************************************************
**      2021-12-07  HTm30RxhjWidget
***************************************************************************************************/

#pragma once

#include <QtUiPlugin/QDesignerExportWidget>
#include <QtWidgets/QWidget>

class HTm30RxhjWidgetPrivate;

class QDESIGNER_WIDGET_EXPORT HTm30RxhjWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HTm30RxhjWidget(QWidget *parent = nullptr);
    ~HTm30RxhjWidget() override;

public:
    void setRcshj(QList<double>);
    void setRhshj(QList<double>);
    void setRfhj(QList<double>);

protected:
    void init();

protected:
    QScopedPointer<HTm30RxhjWidgetPrivate> d_ptr;
};



