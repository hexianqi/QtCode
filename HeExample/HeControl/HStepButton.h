/***************************************************************************************************
**      2020-04-01  HStepButton 路径按钮组。
**                  https://qtdebug.com/qtbook-custom-widget-steps/
***************************************************************************************************/

#pragma once

#include "HNamespace.h"
#include <QtWidgets/QWidget>

HE_BEGIN_NAMESPACE

class HStepButtonPrivate;

class HStepButton : public QWidget
{
    Q_OBJECT

public:
    explicit HStepButton(QWidget *parent = nullptr);
    ~HStepButton() override;

public:
    void setButton(QStringList value);

protected:
    HStepButton(HStepButtonPrivate &p, QWidget *parent = nullptr);

protected slots:
    void updateStatus();

protected:
    QScopedPointer<HStepButtonPrivate> d_ptr;

private:
    void init();
};

HE_END_NAMESPACE
