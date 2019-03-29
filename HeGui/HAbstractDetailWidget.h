/***************************************************************************************************
**      2019-03-26  HAbstractDetailWidget   抽象详情窗体类。
***************************************************************************************************/

#ifndef HABSTRACTDETAILWIDGET_H
#define HABSTRACTDETAILWIDGET_H

#include "IDetailWidget.h"

HE_GUI_BEGIN_NAMESPACE

class HAbstractDetailWidgetPrivate;

class HE_GUI_EXPORT HAbstractDetailWidget : public IDetailWidget
{
    Q_OBJECT
public:
    explicit HAbstractDetailWidget(QWidget *parent = nullptr);
    ~HAbstractDetailWidget() override;

public:
    void initialize(QVariantMap param) override;

protected:
    HAbstractDetailWidget(HAbstractDetailWidgetPrivate &p, QWidget *parent = nullptr);

protected:
    QScopedPointer<HAbstractDetailWidgetPrivate> d_ptr;
};

HE_GUI_END_NAMESPACE

#endif // HABSTRACTDETAILWIDGET_H
