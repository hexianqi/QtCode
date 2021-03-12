/***************************************************************************************************
**      2019-07-31  HClearLineEdit
***************************************************************************************************/

#pragma once

#include "HButtonLineEdit.h"

HE_CONTROL_BEGIN_NAMESPACE

class HClearLineEditPrivate;

class HClearLineEdit : public HButtonLineEdit
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HClearLineEdit)

public:
    explicit HClearLineEdit(QWidget *parent = nullptr);

public slots:
    void setButtonVisible(bool b) override;

protected:
    HClearLineEdit(HClearLineEditPrivate &p, QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *) override;

private:
    void init();
};

HE_CONTROL_END_NAMESPACE
