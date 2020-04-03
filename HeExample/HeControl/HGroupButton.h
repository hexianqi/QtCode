/***************************************************************************************************
**      2020-04-02  HGroupButton 组按钮
**                  https://qtdebug.com/qtbook-custom-widget-group-buttons/
***************************************************************************************************/

#ifndef HGROUPBUTTON_H
#define HGROUPBUTTON_H

#include "HControlGlobal.h"
#include <QtWidgets/QWidget>

HE_CONTROL_BEGIN_NAMESPACE

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

HE_CONTROL_END_NAMESPACE

#endif // HGROUPBUTTON_H
