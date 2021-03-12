/***************************************************************************************************
**      2020-04-09  HImageSwitch 图片开关控件
**                  https://gitee.com/feiyangqingyun/QWidgetDemo
**                  1:自带三种开关按钮样式
**                  2:可自定义开关图片
***************************************************************************************************/

#pragma once

#include "HControlGlobal.h"
#include <QtWidgets/QWidget>

HE_CONTROL_BEGIN_NAMESPACE

class HImageSwitchPrivate;

class HImageSwitch : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(bool checked             READ isChecked      WRITE setChecked)
    Q_PROPERTY(ButtonStyle buttonStyle  READ buttonStyle    WRITE setButtonStyle)

public:
    enum ButtonStyle
    {
        ButtonStyle_1 = 0,
        ButtonStyle_2 = 1,
        ButtonStyle_3 = 2
    };
    Q_ENUM(ButtonStyle)

public:
    explicit HImageSwitch(QWidget *parent = nullptr);
    ~HImageSwitch() override;

signals:
    void clicked();

public:
    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;
    bool isChecked() const;
    ButtonStyle buttonStyle() const;

public slots:
    void setChecked(bool b);
    void setButtonStyle(ButtonStyle value);

protected:
    HImageSwitch(HImageSwitchPrivate &p, QWidget *parent = nullptr);

protected:
    void mousePressEvent(QMouseEvent *) override;
    void paintEvent(QPaintEvent *) override;

protected:
    QScopedPointer<HImageSwitchPrivate> d_ptr;
};

HE_CONTROL_END_NAMESPACE
