/***************************************************************************************************
**      2020-04-02  HAbnormityButton 异形按钮组。
**                  https://qtdebug.com/qtbook-custom-widget-abnormity-buttons/
***************************************************************************************************/

#pragma once

#include "HNamespace.h"
#include <QtWidgets/QWidget>

HE_BEGIN_NAMESPACE

class HAbnormityButtonPrivate;

class HAbnormityButton : public QWidget
{
    Q_OBJECT

public:
    explicit HAbnormityButton(QWidget *parent = nullptr);
    ~HAbnormityButton() override;

protected:
    HAbnormityButton(HAbnormityButtonPrivate &p, QWidget *parent = nullptr);

protected:
    QScopedPointer<HAbnormityButtonPrivate> d_ptr;

private:
    void init();
};

HE_END_NAMESPACE
