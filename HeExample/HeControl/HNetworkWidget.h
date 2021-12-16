/***************************************************************************************************
**      2019-07-18  HNetworkWidget
***************************************************************************************************/

#pragma once

#include "HNamespace.h"
#include <QtWidgets/QWidget>

HE_BEGIN_NAMESPACE

class HNetworkWidgetPrivate;

class HNetworkWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HNetworkWidget(QWidget *parent = nullptr);
    ~HNetworkWidget() override;

protected:
    HNetworkWidget(HNetworkWidgetPrivate &p, QWidget *parent = nullptr);

protected:
    QScopedPointer<HNetworkWidgetPrivate> d_ptr;

private:
    void init();
};

HE_END_NAMESPACE
