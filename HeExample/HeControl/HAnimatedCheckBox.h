/***************************************************************************************************
**      2020-04-02  HAnimatedCheckBox
**                  https://qtdebug.com/qtbook-animated-checkbox/
***************************************************************************************************/

#pragma once

#include "HControlGlobal.h"
#include <QtWidgets/QCheckBox>

HE_CONTROL_BEGIN_NAMESPACE

class HAnimatedCheckBoxPrivate;

class HAnimatedCheckBox : public QCheckBox
{
    Q_OBJECT

public:
    explicit HAnimatedCheckBox(QWidget *parent = nullptr);
    ~HAnimatedCheckBox() override;

protected:
    HAnimatedCheckBox(HAnimatedCheckBoxPrivate &p, QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *) override;
    void resizeEvent(QResizeEvent *) override;
    void mousePressEvent(QMouseEvent *) override;

protected:
    QScopedPointer<HAnimatedCheckBoxPrivate> d_ptr;

private:
    void init();
    void handleToggled();
};

HE_CONTROL_END_NAMESPACE
