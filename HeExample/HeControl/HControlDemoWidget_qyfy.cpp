#include "HControlDemoWidget_p.h"
#include "HBattery.h"
#include "HCpuMemoryLabel.h"
#include "HDeviceButton.h"
#include "HDiskSizeTable.h"
#include "HFlatStyle.h"
#include "HImageSwitch.h"
#include "HIPAddress.h"
#include "HLightButton.h"
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>

HE_BEGIN_NAMESPACE

void HControlDemoWidget::addFYQY()
{
    addBattery();
    addDeviceButton();
    addExplorer();
    addImageSwitch();
    addIPAddress();
    addLightButton();
}

void HControlDemoWidget::addBattery()
{
    auto battery = new HBattery;
    auto slider = new QSlider;
    slider->setOrientation(Qt::Horizontal);
    slider->setSingleStep(10);

    auto layout = new QGridLayout;
    layout->addWidget(battery, 0, 0);
    layout->addWidget(slider, 1, 0);

    d_ptr->style->setStyle(slider, 8, "#505050", "#1ABC9C", "#1ABC9C");
    connect(slider, &QSlider::valueChanged, battery, &HBattery::setValue);
    addTab(tr("飞扬青云"), tr("电池电量"), layout);
}

void HControlDemoWidget::addDeviceButton()
{
    QHash<QString, HDeviceButton::ButtonStyle> style;
    style.insert(tr("圆形"),  HDeviceButton::ButtonStyle_Circle);
    style.insert(tr("警察"),  HDeviceButton::ButtonStyle_Police);
    style.insert(tr("气泡"),  HDeviceButton::ButtonStyle_Bubble);
    style.insert(tr("气泡2"), HDeviceButton::ButtonStyle_Bubble2);
    style.insert(tr("消息"),  HDeviceButton::ButtonStyle_Msg);
    style.insert(tr("消息2"), HDeviceButton::ButtonStyle_Msg2);

    QHash<QString, HDeviceButton::ButtonColor> color;
    color.insert(tr("绿色"), HDeviceButton::ButtonColor_Green);
    color.insert(tr("蓝色"), HDeviceButton::ButtonColor_Blue);
    color.insert(tr("红色"), HDeviceButton::ButtonColor_Red);
    color.insert(tr("灰色"), HDeviceButton::ButtonColor_Gray);
    color.insert(tr("黑色"), HDeviceButton::ButtonColor_Black);
    color.insert(tr("紫色"), HDeviceButton::ButtonColor_Purple);
    color.insert(tr("黄色"), HDeviceButton::ButtonColor_Yellow);

    auto label = new QLabel;
    label->setFrameShape(QFrame::Box);
    label->setFrameShadow(QFrame::Sunken);
    label->setAlignment(Qt::AlignCenter);
    label->setStyleSheet("border-image:url(:/fyqy/devicebutton/defence_button_bk.jpg);");

    auto deviceButton1 = new HDeviceButton(label);
    deviceButton1->setText("#1");
    deviceButton1->setGeometry(5, 5, 35, 35);
    auto deviceButton2 = new HDeviceButton(label);
    deviceButton2->setText("#2");
    deviceButton2->setGeometry(45, 5, 35, 35);
    auto deviceButton3 = new HDeviceButton(label);
    deviceButton3->setText("#3");
    deviceButton3->setGeometry(85, 5, 35, 35);

    auto changeStyle = [=] {
        auto pushButton = qobject_cast<QPushButton *>(sender());
        auto style = pushButton->property("buttonStyle").value<HDeviceButton::ButtonStyle>();
        deviceButton1->setButtonStyle(style);
        deviceButton2->setButtonStyle(style);
        deviceButton3->setButtonStyle(style);
    };
    auto changeStatus = [=] {
        auto pushButton = qobject_cast<QPushButton *>(sender());
        auto status = pushButton->property("buttonStatus").value<HDeviceButton::ButtonColor>();
        deviceButton1->setButtonColor(status);
        deviceButton2->setButtonColor(status);
        deviceButton3->setButtonColor(status);
    };
    auto changeMove = [=](int value) {
        deviceButton1->setMoveEnable(value != 0);
        deviceButton2->setMoveEnable(value != 0);
        deviceButton3->setMoveEnable(value != 0);
    };

    auto frame = new QFrame;
    frame->setMaximumSize(QSize(100, 16777215));
    frame->setFrameShape(QFrame::Box);
    frame->setFrameShadow(QFrame::Sunken);
    auto vlayout = new QVBoxLayout(frame);

    for (auto i = style.begin(); i != style.end(); i++)
    {
        auto pushButton = new QPushButton(i.key());
        pushButton->setProperty("buttonStyle", i.value());
        vlayout->addWidget(pushButton);
        connect(pushButton, &QPushButton::clicked, this, changeStyle);
    }

    auto line = new QFrame(frame);
    line->setFrameShape(QFrame::HLine);
    line->setFrameShadow(QFrame::Sunken);
    vlayout->addWidget(line);

    for (auto i = color.begin(); i != color.end(); i++)
    {
        auto pushButton = new QPushButton(i.key());
        pushButton->setProperty("buttonStatus", i.value());
        vlayout->addWidget(pushButton);
        connect(pushButton, &QPushButton::clicked, this, changeStatus);
    }

    auto check = new QCheckBox(tr("可移动"));
    check->setChecked(true);
    connect(check, &QCheckBox::stateChanged, this, changeMove);

    vlayout->addWidget(check);
    vlayout->addStretch();

    auto hlayout = new QHBoxLayout;
    hlayout->addWidget(label);
    hlayout->addWidget(frame);
    addTab(tr("飞扬青云"), tr("设备按钮"), hlayout);
}

void HControlDemoWidget::addExplorer()
{
    auto label = new HCpuMemoryLabel();
    auto table = new HDiskSizeTable();
    label->setFont(QFont("Microsoft Yahei", 13));
    label->setStyleSheet("QLabel{ background-color: #000000; color: #64B8FF; }");
    label->start(1500);
    auto layout = new QGridLayout;
    layout->addWidget(label, 0, 0);
    layout->addWidget(table, 1, 0);
    addTab(tr("飞扬青云"), tr("资源管理器"), layout);
}

void HControlDemoWidget::addImageSwitch()
{
    auto button1 = new HImageSwitch;
    auto button2 = new HImageSwitch;
    auto button3 = new HImageSwitch;
    button1->setButtonStyle(HImageSwitch::ButtonStyle_1);
    button2->setButtonStyle(HImageSwitch::ButtonStyle_2);
    button3->setButtonStyle(HImageSwitch::ButtonStyle_3);
    auto layout = new QHBoxLayout;
    layout->addWidget(button1);
    layout->addWidget(button2);
    layout->addWidget(button3);
    addTab(tr("飞扬青云"), tr("图片开关按钮"), layout);
}

void HControlDemoWidget::addIPAddress()
{
    addTab(tr("飞扬青云"), new HIPAddress);
}

void HControlDemoWidget::addLightButton()
{
    auto button1 = new HLightButton;
    auto button2 = new HLightButton;
    auto button3 = new HLightButton;
    button2->setBackground(QColor(255, 107, 107));
    button3->setBackground(QColor(24, 189, 155));
    auto layout = new QHBoxLayout;
    layout->addWidget(button1);
    layout->addWidget(button2);
    layout->addWidget(button3);
    addTab(tr("飞扬青云"), tr("发光按钮"), layout);
}

HE_END_NAMESPACE
