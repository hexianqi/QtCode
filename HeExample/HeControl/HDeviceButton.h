/***************************************************************************************************
**      2018-07-02  HDefenceButton 设备按钮控件
**                  https://gitee.com/feiyangqingyun/QWidgetDemo
**                  1:可设置防区样式  圆形、警察、气泡、气泡2、消息、消息2
**                  2:可设置防区状态  布防、撤防、报警、旁路、故障
**                  3:可设置报警切换
**                  4:可设置显示的防区号
**                  5:可设置是否可鼠标拖动
**                  6:发出单击和双击信号
***************************************************************************************************/

#pragma once

#include "HNamespace.h"
#include <QtWidgets/QWidget>

HE_BEGIN_NAMESPACE

class HDeviceButtonPrivate;

class HDeviceButton : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(bool moveEnable          READ isMoveEnable   WRITE setMoveEnable)
    Q_PROPERTY(QString text             READ text           WRITE setText)
    Q_PROPERTY(ButtonStyle buttonStyle  READ buttonStyle    WRITE setButtonStyle)
    Q_PROPERTY(ButtonColor buttonColor  READ buttonColor    WRITE setButtonColor)

public:
    enum ButtonStyle
    {
        ButtonStyle_Circle = 0,     // 圆形
        ButtonStyle_Police = 1,     // 警察
        ButtonStyle_Bubble = 2,     // 气泡
        ButtonStyle_Bubble2 = 3,    // 气泡2
        ButtonStyle_Msg = 4,        // 消息
        ButtonStyle_Msg2 = 5        // 消息2
    };
    Q_ENUM(ButtonStyle)

    enum ButtonColor
    {
        ButtonColor_Green = 0,      // 绿色 激活状态
        ButtonColor_Blue = 1,       // 蓝色 在线状态
        ButtonColor_Red = 2,        // 红色 报警状态
        ButtonColor_Gray = 3,       // 灰色 离线状态
        ButtonColor_Black = 4,      // 黑色 故障状态
        ButtonColor_Purple = 5,     // 紫色 其他状态
        ButtonColor_Yellow = 6      // 黄色 其他状态
    };
    Q_ENUM(ButtonColor)

public:
    explicit HDeviceButton(QWidget *parent = nullptr);
    ~HDeviceButton() override;

signals:
    void clicked();
    void doubleClicked();

public:
    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;
    bool isMoveEnable() const;
    QString text() const;
    ButtonStyle buttonStyle() const;
    ButtonColor buttonColor() const;

public slots:
    void setMoveEnable(bool b);
    void setText(const QString &value);
    void setButtonStyle(ButtonStyle value);
    void setButtonColor(ButtonColor value);
    void checkAlarm();

protected:
    HDeviceButton(HDeviceButtonPrivate &p, QWidget *parent = nullptr);

protected:
    void mousePressEvent(QMouseEvent *) override;
    void mouseDoubleClickEvent(QMouseEvent *) override;
    void paintEvent(QPaintEvent *) override;
    void drawPixmap(QPainter *);
    void drawText(QPainter *);

protected:
    QScopedPointer<HDeviceButtonPrivate> d_ptr;

private:
    void init();
    void updatePixmap();
};

HE_END_NAMESPACE
