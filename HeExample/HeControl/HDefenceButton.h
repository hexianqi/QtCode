/***************************************************************************************************
**      2018-07-02  HDefenceButton 防区按钮控件
**                  https://gitee.com/feiyangqingyun/QWidgetDemo
**                  1:可设置防区样式  圆形、警察、气泡、气泡2、消息、消息2
**                  2:可设置防区状态  布防、撤防、报警、旁路、故障
**                  3:可设置报警切换
**                  4:可设置显示的防区号
**                  5:可设置是否可鼠标拖动
**                  6:发出单击和双击信号
***************************************************************************************************/

#ifndef HDEFENCEBUTTON_H
#define HDEFENCEBUTTON_H

#include "HControlGlobal.h"
#include <QtWidgets/QWidget>

HE_CONTROL_BEGIN_NAMESPACE

class HDefenceButtonPrivate;

class HDefenceButton : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(bool moveEnable READ isMoveEnable WRITE setMoveEnable)
    Q_PROPERTY(QString text READ text WRITE setText)
    Q_PROPERTY(ButtonStyle buttonStyle READ buttonStyle WRITE setButtonStyle)
    Q_PROPERTY(ButtonStatus buttonStatus READ buttonStatus WRITE setButtonStatus)

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

    enum ButtonStatus
    {
        ButtonStatus_Arming = 0,    // 布防
        ButtonStatus_Disarming = 1, // 撤防
        ButtonStatus_Alarm = 2,     // 报警
        ButtonStatus_Bypass = 3,    // 旁路
        ButtonStatus_Error = 4      // 故障
    };
    Q_ENUM(ButtonStatus)

public:
    explicit HDefenceButton(QWidget *parent = nullptr);
    ~HDefenceButton() override;

signals:
    void clicked();
    void doubleClicked();

public:
    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;
    bool isMoveEnable() const;
    QString text() const;
    ButtonStyle buttonStyle() const;
    ButtonStatus buttonStatus() const;

public slots:
    void setMoveEnable(bool b);
    void setText(const QString &value);
    void setButtonStyle(ButtonStyle value);
    void setButtonStatus(ButtonStatus value);
    void alarm();

protected:
    HDefenceButton(HDefenceButtonPrivate &p, QWidget *parent = nullptr);

protected:
    void mousePressEvent(QMouseEvent *) override;
    void mouseDoubleClickEvent(QMouseEvent *) override;
    void paintEvent(QPaintEvent *) override;
    void drawPixmap(QPainter *);
    void drawText(QPainter *);

protected:
    QScopedPointer<HDefenceButtonPrivate> d_ptr;

private:
    void init();
    void updatePixmap();
};

HE_CONTROL_END_NAMESPACE

#endif // HDEFENCEBUTTON_H
