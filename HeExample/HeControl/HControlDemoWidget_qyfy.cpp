#include "HControlDemoWidget_p.h"
#include "HBattery.h"
#include "HCpuMemoryLabel.h"
#include "HDeviceButton.h"
#include "HDiskSizeTable.h"
#include "HFlatStyle.h"
#include "HImageSwitch.h"
#include "HIPAddress.h"
#include "HLightButton.h"
#include "HNavButton.h"
#include "HDrawHelper.h"
#include "IIconFontFactory.h"
#include <QtGui/QPen>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QCheckBox>

HE_BEGIN_NAMESPACE

void HControlDemoWidget::addFYQY()
{
    addBattery();
    addDeviceButton();
    addExplorer();
    addImageSwitch();
    addIPAddress();
    addLightButton();
    addNavButton();
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
    label->setStyleSheet("border-image:url(:/Resources/fyqy/devicebutton/defence_button_bk.jpg);");

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

void HControlDemoWidget::addNavButton()
{
    auto layout1 = new QVBoxLayout;
    auto layout2 = new QVBoxLayout;
    auto layout3 = new QVBoxLayout;
    auto layout4 = new QVBoxLayout;
    auto layout5 = new QHBoxLayout;
    layout5->setSpacing(0);
    auto layout6 = new QHBoxLayout;
    layout6->setSpacing(0);
    auto layout7 = new QHBoxLayout;
    layout7->setSpacing(0);
    auto iconFont = d_ptr->iconFactory->createFont("FontAwesome");
    iconFont.setPixelSize(15);
    QFont font;
    font.setPixelSize(15);
    font.setBold(true);

    auto list1 = QStringList() << tr("学生管理") << tr("教师管理") << tr("成绩管理") << tr("记录查询");
    auto list2 = QStringList() << tr("首页") << tr("作品") << tr("论坛") << tr("群组") << tr("帮助");
    auto list3 = QStringList() << tr("首页") << tr("论坛") << tr("Qt下载") << tr("作品展") << tr("群组") << tr("个人中心");
    auto chars = QList<QChar>() << 0xf17b << 0xf002 << 0xf013 << 0xf021 << 0xf0e0 << 0xf135;

    // 例1
    {
        auto iconNormal = QPixmap::fromImage(HDrawHelper::createFontImage(iconFont, 0xf061, QSize(15, 15), QColor("#646464")));
        auto iconHover = QPixmap::fromImage(HDrawHelper::createFontImage(iconFont, 0xf061, QSize(15, 15), QColor("#FFFFFF")));
        auto iconCheck = QPixmap::fromImage(HDrawHelper::createFontImage(iconFont, 0xf061, QSize(15, 15), QColor("#FFFFFF")));
        for (int i = 0; i < list1.size(); i++)
        {
            auto button = new HNavButton;
            button->setText(list1[i]);
            button->setPaddingLeft(32);
            button->setLineSpace(6);
            button->setShowIcon(true);
            button->setIconSpace(15);
            button->setIconSize(QSize(10, 10));
            button->setIconNormal(iconNormal);
            button->setIconHover(iconHover);
            button->setIconCheck(iconCheck);
            layout1->addWidget(button);
        }
    }
    // 例2
    {
        auto normalBackground = QColor("#2D9191");
        auto hoverBackground = QColor("#187294");
        auto checkBackground = QColor("#145C75");
        auto normalTextColor = QColor("#FFFFFF");
        auto hoverTextColor = QColor("#FFFFFF");
        auto checkTextColor = QColor("#FFFFFF");
        for (int i = 0; i < list1.size(); i++)
        {
            auto iconNormal = QPixmap::fromImage(HDrawHelper::createFontImage(iconFont, chars[i], QSize(20, 20), normalTextColor));
            auto iconHover = QPixmap::fromImage(HDrawHelper::createFontImage(iconFont, chars[i], QSize(20, 20), hoverTextColor));
            auto iconCheck = QPixmap::fromImage(HDrawHelper::createFontImage(iconFont, chars[i], QSize(20, 20), checkTextColor));
            auto button = new HNavButton;
            button->setText(list1[i]);
            button->setPaddingLeft(35);
            button->setLineSpace(0);
            button->setLineWidth(8);
            button->setLineColor(QColor(255, 107, 107));
            button->setShowTriangle(true);
            button->setShowIcon(true);
            button->setIconSpace(10);
            button->setIconSize(QSize(22, 22));
            button->setIconNormal(iconNormal);
            button->setIconHover(iconHover);
            button->setIconCheck(iconCheck);
            button->setNormalBackground(normalBackground);
            button->setHoverBackground(hoverBackground);
            button->setCheckBackground(checkBackground);
            button->setNormalTextColor(normalTextColor);
            button->setHoverTextColor(hoverTextColor);
            button->setCheckTextColor(checkTextColor);
            layout2->addWidget(button);
        }
    }
    // 例3
    {
        auto normalBackground = QColor("#292F38");
        auto hoverBackground = QColor("#1D2025");
        auto checkBackground = QColor("#1D2025");
        auto normalTextColor = QColor("#54626F");
        auto hoverTextColor = QColor("#FDFDFD");
        auto checkTextColor = QColor("#FDFDFD");
        for (int i = 0; i < list1.size(); i++)
        {
            auto iconNormal = QPixmap::fromImage(HDrawHelper::createFontImage(iconFont, chars[i], QSize(20, 20), normalTextColor));
            auto iconHover = QPixmap::fromImage(HDrawHelper::createFontImage(iconFont, chars[i], QSize(20, 20), hoverTextColor));
            auto iconCheck = QPixmap::fromImage(HDrawHelper::createFontImage(iconFont, chars[i], QSize(20, 20), checkTextColor));
            auto button = new HNavButton;
            button->setText(list1[i]);
            button->setPaddingLeft(35);
            button->setLineWidth(10);
            button->setLineColor(QColor("#029FEA"));
            button->setShowTriangle(true);
            button->setTextAlign(Qt::AlignLeft);
            button->setTrianglePosition(HControlType::Position_Left);
            button->setLinePosition(HControlType::Position_Right);
            button->setShowIcon(true);
            button->setIconSpace(10);
            button->setIconSize(QSize(22, 22));
            button->setIconNormal(iconNormal);
            button->setIconHover(iconHover);
            button->setIconCheck(iconCheck);
            button->setNormalBackground(normalBackground);
            button->setHoverBackground(hoverBackground);
            button->setCheckBackground(checkBackground);
            button->setNormalTextColor(normalTextColor);
            button->setHoverTextColor(hoverTextColor);
            button->setCheckTextColor(checkTextColor);
            layout3->addWidget(button);
        }
    }
    // 例4
    {
        auto iconNormal = QPixmap::fromImage(HDrawHelper::createFontImage(iconFont, 0xf105, QSize(15, 15), QColor("#646464")));
        auto iconHover = QPixmap::fromImage(HDrawHelper::createFontImage(iconFont, 0xf105, QSize(15, 15), QColor("#FFFFFF")));
        auto iconCheck = QPixmap::fromImage(HDrawHelper::createFontImage(iconFont, 0xf105, QSize(15, 15), QColor("#FFFFFF")));
        for (int i = 0; i < list1.size(); i++)
        {
            auto button = new HNavButton;
            button->setText(list1[i]);
            button->setLineSpace(10);
            button->setLineWidth(10);
            button->setPaddingRight(25);
            button->setShowTriangle(true);
            button->setTextAlign(Qt::AlignRight);
            button->setTrianglePosition(HControlType::Position_Left);
            button->setLinePosition(HControlType::Position_Right);
            button->setShowIcon(true);
            button->setIconSpace(25);
            button->setIconSize(QSize(15, 15));
            button->setIconNormal(iconNormal);
            button->setIconHover(iconHover);
            button->setIconCheck(iconCheck);
            layout4->addWidget(button);
        }
    }
    // 例5
    {
        auto normalBackground = QColor("#292929");
        auto hoverBackground = QColor("#064077");
        auto checkBackground = QColor("#10689A");
        auto normalTextColor = QColor("#FFFFFF");
        auto hoverTextColor = QColor("#FFFF00");
        auto checkTextColor = QColor("#FFFFFF");
        for (int i = 0; i < list2.size(); i++)
        {
            auto iconNormal = QPixmap::fromImage(HDrawHelper::createFontImage(iconFont, chars[i], QSize(20, 20), normalTextColor));
            auto iconHover = QPixmap::fromImage(HDrawHelper::createFontImage(iconFont, chars[i], QSize(20, 20), hoverTextColor));
            auto iconCheck = QPixmap::fromImage(HDrawHelper::createFontImage(iconFont, chars[i], QSize(20, 20), checkTextColor));
            auto button = new HNavButton;
            button->setText(list2[i]);
            button->setFont(font);
            button->setPaddingLeft(20);
            button->setShowLine(false);
            button->setTextAlign(Qt::AlignCenter);
            button->setLinePosition(HControlType::Position_Bottom);
            button->setShowIcon(true);
            button->setIconSpace(15);
            button->setIconSize(QSize(22, 22));
            button->setIconNormal(iconNormal);
            button->setIconHover(iconHover);
            button->setIconCheck(iconCheck);
            button->setNormalBackground(normalBackground);
            button->setHoverBackground(hoverBackground);
            button->setCheckBackground(checkBackground);
            button->setNormalTextColor(normalTextColor);
            button->setHoverTextColor(hoverTextColor);
            button->setCheckTextColor(checkTextColor);
            layout5->addWidget(button);
        }
    }
    // 例6
    {
        auto normalBackground = QColor("#E6393D");
        auto hoverBackground = QColor("#EE0000");
        auto checkBackground = QColor("#A40001");
        auto normalTextColor = QColor("#FFFFFF");
        auto hoverTextColor = QColor("#FFFFFF");
        auto checkTextColor = QColor("#FFFFFF");
        for (int i = 0; i < list2.size(); i++)
        {
            auto iconNormal = QPixmap::fromImage(HDrawHelper::createFontImage(iconFont, chars[i], QSize(20, 20), normalTextColor));
            auto iconHover = QPixmap::fromImage(HDrawHelper::createFontImage(iconFont, chars[i], QSize(20, 20), hoverTextColor));
            auto iconCheck = QPixmap::fromImage(HDrawHelper::createFontImage(iconFont, chars[i], QSize(20, 20), checkTextColor));
            auto button = new HNavButton;
            button->setText(list2[i]);
            button->setFont(font);
            button->setPaddingLeft(20);
            button->setShowLine(false);
            button->setTextAlign(Qt::AlignCenter);
            button->setLinePosition(HControlType::Position_Bottom);
            button->setShowIcon(true);
            button->setIconSpace(15);
            button->setIconSize(QSize(22, 22));
            button->setIconNormal(iconNormal);
            button->setIconHover(iconHover);
            button->setIconCheck(iconCheck);
            button->setNormalBackground(normalBackground);
            button->setHoverBackground(hoverBackground);
            button->setCheckBackground(checkBackground);
            button->setNormalTextColor(normalTextColor);
            button->setHoverTextColor(hoverTextColor);
            button->setCheckTextColor(checkTextColor);
            layout6->addWidget(button);
        }
    }
    // 例7
    {
        auto gradient1 = QLinearGradient(0, 0, 0, 30);
        gradient1.setColorAt(0.0, QColor("#3985BF"));
        gradient1.setColorAt(0.5, QColor("#2972A9"));
        gradient1.setColorAt(1.0, QColor("#1C6496"));
        auto gradient2 = QLinearGradient(0, 0, 0, 30);
        gradient2.setColorAt(0.0, QColor("#4897D1"));
        gradient2.setColorAt(0.5, QColor("#3283BC"));
        gradient2.setColorAt(1.0, QColor("#3088C3"));
        auto normalTextColor = QColor("#FFFFFF");
        auto hoverTextColor = QColor("#FFFFFF");
        auto checkTextColor = QColor("#FFFFFF");
        for (int i = 0; i < list3.size(); i++)
        {
            auto button = new HNavButton;
            button->setText(list3[i]);
            button->setFont(font);
            button->setPaddingLeft(0);
            button->setLineSpace(0);
            button->setShowTriangle(true);
            button->setTextAlign(Qt::AlignCenter);
            button->setTrianglePosition(HControlType::Position_Bottom);
            button->setLinePosition(HControlType::Position_Top);
            button->setNormalTextColor(normalTextColor);
            button->setHoverTextColor(hoverTextColor);
            button->setCheckTextColor(checkTextColor);
            button->setNormalBackgroundBrush(gradient1);
            button->setHoverBackgroundBrush(gradient2);
            button->setCheckBackgroundBrush(gradient2);
            layout7->addWidget(button);
        }
    }
    auto layout = new QGridLayout;
    layout->addLayout(layout1, 0, 0);
    layout->addLayout(layout2, 0, 1);
    layout->addLayout(layout3, 0, 2);
    layout->addLayout(layout4, 0, 3);
    layout->addLayout(layout5, 1, 0, 1, 4);
    layout->addLayout(layout6, 2, 0, 1, 4);
    layout->addLayout(layout7, 3, 0, 1, 4);
    layout->addItem(new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding), 4, 0);
    addTab(tr("飞扬青云"), tr("导航按钮"), layout);
}

HE_END_NAMESPACE
