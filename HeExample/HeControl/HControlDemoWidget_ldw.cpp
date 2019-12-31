#include "HControlDemoWidget_p.h"
#include "IIconFontFactory.h"
#include "HFlatStyle.h"
#include "HDrawHelper.h"
#include "HBattery.h"
#include "HDefenceButton.h"
#include "HDiskSizeTable.h"
#include "HImageCalendar.h"
#include "HIPAddress.h"
#include "HLightButton.h"
#include "HLunarCalendarWidget.h"
#include "HNavButton.h"

#include <QtGui/QPen>
#include <QtWidgets/QLabel>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGridLayout>

HE_CONTROL_BEGIN_NAMESPACE

void HControlDemoWidget::addLiuDianWu()
{
    addBattery();
    addCalendar();
    addExplorer();
    addIPAddress();
    addDefenceButton();
    addLightButton();
    addLunarCalendar();
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
    addTab(tr("ludianwu"), tr("电池电量"), layout);
}

void HControlDemoWidget::addCalendar()
{
    addTab(tr("ludianwu"), new HImageCalendar);
}

void HControlDemoWidget::addExplorer()
{

//    auto w = new HCpuMemoryLabel();
    auto table = new HDiskSizeTable();
//    w->setFont(QFont("Microsoft Yahei", 13));
//    w->setStyleSheet("QLabel{ background-color: #000000; color: #64B8FF; }");
//    w->start(1500);
//    layout->addWidget(w, 0, 0);
    auto layout = new QGridLayout;
    layout->addWidget(table, 1, 0);
    addTab(tr("ludianwu"), tr("资源管理器"), layout);
}

void HControlDemoWidget::addIPAddress()
{
    addTab(tr("ludianwu"), new HIPAddress);
}

void HControlDemoWidget::addDefenceButton()
{
    QHash<QString, HDefenceButton::ButtonStyle> style;
    style.insert(tr("圆形"),  HDefenceButton::ButtonStyle_Circle);
    style.insert(tr("警察"),  HDefenceButton::ButtonStyle_Police);
    style.insert(tr("气泡"),  HDefenceButton::ButtonStyle_Bubble);
    style.insert(tr("气泡2"), HDefenceButton::ButtonStyle_Bubble2);
    style.insert(tr("消息"),  HDefenceButton::ButtonStyle_Msg);
    style.insert(tr("消息2"), HDefenceButton::ButtonStyle_Msg2);

    QHash<QString, HDefenceButton::ButtonStatus> status;
    status.insert(tr("布防"), HDefenceButton::ButtonStatus_Arming);
    status.insert(tr("撤防"), HDefenceButton::ButtonStatus_Disarming);
    status.insert(tr("报警"), HDefenceButton::ButtonStatus_Alarm);
    status.insert(tr("旁路"), HDefenceButton::ButtonStatus_Bypass);
    status.insert(tr("故障"), HDefenceButton::ButtonStatus_Error);

    auto label = new QLabel;
    label->setFrameShape(QFrame::Box);
    label->setFrameShadow(QFrame::Sunken);
    label->setAlignment(Qt::AlignCenter);
    label->setStyleSheet("border-image:url(:/image/ludianwu/defence_button_bk.jpg);");

    auto defenceButton1 = new HDefenceButton(label);
    defenceButton1->setText("#1");
    defenceButton1->setGeometry(5, 5, 35, 35);
    auto defenceButton2 = new HDefenceButton(label);
    defenceButton2->setText("#2");
    defenceButton2->setGeometry(45, 5, 35, 35);
    auto defenceButton3 = new HDefenceButton(label);
    defenceButton3->setText("#3");
    defenceButton3->setGeometry(85, 5, 35, 35);

    auto changeStyle = [=] {
        auto pushButton = qobject_cast<QPushButton *>(sender());
        auto style = pushButton->property("buttonStyle").value<HDefenceButton::ButtonStyle>();
        defenceButton1->setButtonStyle(style);
        defenceButton2->setButtonStyle(style);
        defenceButton3->setButtonStyle(style);
    };
    auto changeStatus = [=] {
        auto pushButton = qobject_cast<QPushButton *>(sender());
        auto status = pushButton->property("buttonStatus").value<HDefenceButton::ButtonStatus>();
        defenceButton1->setButtonStatus(status);
        defenceButton2->setButtonStatus(status);
        defenceButton3->setButtonStatus(status);
    };
    auto changeMove = [=](int value) {
        defenceButton1->setMoveEnable(value != 0);
        defenceButton2->setMoveEnable(value != 0);
        defenceButton3->setMoveEnable(value != 0);
    };

    auto frame = new QFrame;
    frame->setMaximumSize(QSize(100, 16777215));
    frame->setFrameShape(QFrame::Box);
    frame->setFrameShadow(QFrame::Sunken);
    auto vLayout = new QVBoxLayout(frame);

    for (auto i = style.begin(); i != style.end(); i++)
    {
        auto pushButton = new QPushButton(i.key());
        pushButton->setProperty("buttonStyle", i.value());
        vLayout->addWidget(pushButton);
        connect(pushButton, &QPushButton::clicked, this, changeStyle);
    }

    auto line = new QFrame(frame);
    line->setFrameShape(QFrame::HLine);
    line->setFrameShadow(QFrame::Sunken);
    vLayout->addWidget(line);

    for (auto i = status.begin(); i != status.end(); i++)
    {
        auto pushButton = new QPushButton(i.key());
        pushButton->setProperty("buttonStatus", i.value());
        vLayout->addWidget(pushButton);
        connect(pushButton, &QPushButton::clicked, this, changeStatus);
    }

    auto check = new QCheckBox(tr("可移动"));
    check->setChecked(true);
    connect(check, &QCheckBox::stateChanged, this, changeMove);

    vLayout->addWidget(check);
    vLayout->addStretch();

    auto hLayout = new QHBoxLayout;
    hLayout->addWidget(label);
    hLayout->addWidget(frame);
    addTab(tr("ludianwu"), tr("布防按钮"), hLayout);
}

void HControlDemoWidget::addLightButton()
{
    auto lightButton1 = new HLightButton;
    auto lightButton2 = new HLightButton;
    auto lightButton3 = new HLightButton;
    lightButton2->setBackground(QColor(255, 107, 107));
    lightButton3->setBackground(QColor(24, 189, 155));

    auto layout = new QHBoxLayout;
    layout->addWidget(lightButton1);
    layout->addWidget(lightButton2);
    layout->addWidget(lightButton3);
    addTab(tr("ludianwu"), tr("发光按钮"), layout);
}

void HControlDemoWidget::addLunarCalendar()
{
    auto label1 = new QLabel(tr("选中样式："));
    auto label2 = new QLabel(tr("星期格式："));
    label1->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    label2->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

    auto comboBox1 = new QComboBox;
    auto comboBox2 = new QComboBox;
    comboBox1->addItem(tr("矩形背景"), HLunarCalendarItem::SelectType_Rect);
    comboBox1->addItem(tr("圆形背景"), HLunarCalendarItem::SelectType_Circle);
    comboBox1->addItem(tr("角标背景"), HLunarCalendarItem::SelectType_Triangle);
    comboBox1->addItem(tr("图片背景"), HLunarCalendarItem::SelectType_Image);
    comboBox2->addItem(tr("短名称"),   HLunarCalendarWidget::WeekNameFormat_Short);
    comboBox2->addItem(tr("普通名称"), HLunarCalendarWidget::WeekNameFormat_Normal);
    comboBox2->addItem(tr("长名称"),   HLunarCalendarWidget::WeekNameFormat_Long);
    comboBox2->addItem(tr("英文名称"), HLunarCalendarWidget::WeekNameFormat_En);

    auto checkCox = new QCheckBox(tr("显示农历"));
    checkCox->setChecked(true);

    auto widget = new HLunarCalendarWidget;

    auto hLayout = new QHBoxLayout;
    hLayout->addWidget(label1, 1);
    hLayout->addWidget(comboBox1, 3);
    hLayout->addWidget(label2, 1);
    hLayout->addWidget(comboBox2, 3);
    hLayout->addWidget(checkCox, 2);

    auto vLayout = new QVBoxLayout;
    vLayout->addWidget(widget);
    vLayout->addLayout(hLayout);

    connect(comboBox1, &QComboBox::currentTextChanged, this, [=] { widget->setSelectType(comboBox1->currentData().value<HLunarCalendarItem::SelectType>()); });
    connect(comboBox2, &QComboBox::currentTextChanged, this, [=] { widget->setWeekNameFormat(comboBox2->currentData().value<HLunarCalendarWidget::WeekNameFormat>()); });
    connect(checkCox, &QCheckBox::clicked, this, [=](bool b) { widget->setShowLunar(b); });
    addTab(tr("ludianwu"), tr("农历"), vLayout);
}

void HControlDemoWidget::addNavButton()
{
    auto layout1 = new QVBoxLayout;
    auto layout2 = new QVBoxLayout;
    auto layout3 = new QVBoxLayout;
    auto layout4 = new QVBoxLayout;
    auto layout5 = new QHBoxLayout;
    auto layout6 = new QHBoxLayout;
    auto iconFont = d_ptr->iconFactory->createFont("FontAwesome");
    iconFont.setPixelSize(15);
    QFont font;
    font.setPixelSize(15);
    font.setBold(true);

    auto list1 = QStringList() << tr("学生管理") << tr("教师管理") << tr("成绩管理") << tr("记录查询");
    auto list2 = QStringList() << tr("首页") << tr("作品") << tr("论坛") << tr("群组") << tr("帮助");
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
        auto gradient1 = QLinearGradient(0, 0, 0, 30);
        gradient1.setColorAt(0.0, QColor("#3985BF"));
        gradient1.setColorAt(0.5, QColor("#2972A9"));
        gradient1.setColorAt(1.0, QColor("#1C6496"));
        auto gradient2 = QLinearGradient(0, 0, 0, 30);
        gradient2.setColorAt(0.0, QColor("#4897D1"));
        gradient2.setColorAt(0.5, QColor("#3283BC"));
        gradient2.setColorAt(1.0, QColor("#3088C3"));
        auto normalTextColor = QColor("#FFFFFF");
        auto hoverTextColor = QColor("#FFFF00");
        auto checkTextColor = QColor("#FFFFFF");
        for (int i = 0; i < list2.size(); i++)
        {
            auto button = new HNavButton;
            button->setText(list2[i]);
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
            layout6->addWidget(button);
        }
    }
    auto layout = new QGridLayout;
    layout->addLayout(layout1, 0, 0);
    layout->addLayout(layout2, 0, 1);
    layout->addLayout(layout3, 0, 2);
    layout->addLayout(layout4, 0, 3);
    layout->addLayout(layout5, 1, 0, 1, 4);
    layout->addLayout(layout6, 2, 0, 1, 4);
    layout->addItem(new QSpacerItem(20, 20), 3, 0, 1, 4);
    layout->setRowStretch(3, 1);
    addTab(tr("ludianwu"), tr("导航按钮"), layout);
}

HE_CONTROL_END_NAMESPACE
