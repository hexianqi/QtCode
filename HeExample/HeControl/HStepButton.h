/***************************************************************************************************
**      2020-04-01  HStepButton 路径按钮组。
**                  https://qtdebug.com/qtbook-custom-widget-steps/
***************************************************************************************************/

#ifndef HSTEPBUTTTON_H
#define HSTEPBUTTTON_H

#include "HControlGlobal.h"
#include <QtWidgets/QWidget>

HE_CONTROL_BEGIN_NAMESPACE

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

HE_CONTROL_END_NAMESPACE

#endif // HSTEPBUTTTON_H
