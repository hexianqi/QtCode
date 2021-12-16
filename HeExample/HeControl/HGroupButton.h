/***************************************************************************************************
**      2020-04-02  HGroupButton 组按钮
**                  https://qtdebug.com/qtbook-custom-widget-group-buttons/
***************************************************************************************************/

#pragma once

#include "HNamespace.h"
#include <QtWidgets/QWidget>

HE_BEGIN_NAMESPACE

class HGroupButtonPrivate;

class HGroupButton : public QWidget
{
    Q_OBJECT

public:
    explicit HGroupButton(QWidget *parent = nullptr);
    ~HGroupButton() override;

public:
    void setButton(QStringList value);

protected:
    HGroupButton(HGroupButtonPrivate &p, QWidget *parent = nullptr);

protected:
    QScopedPointer<HGroupButtonPrivate> d_ptr;

private:
    void init();
};

HE_END_NAMESPACE
