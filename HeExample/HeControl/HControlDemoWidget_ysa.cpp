#include "HControlDemoWidget_p.h"
#include "HGraphicsDemoWidget.h"
#include "HChatWidget.h"
#include "HComboBoxTableView.h"
#include "HDiscButton.h"
#include "HOnOffWidget.h"
#include "HLotteryTurntableWidget.h"
#include "HTimeSlider.h"
#include "HTimelineWidget.h"
#include "HColorSelectionRing.h"
#include "HColorGradientRoundedButton.h"
#include "HProcessDisplayWidget.h"
#include "HIrregularPopupWidget.h"
#include "HPatternLockWidget.h"
#include "HRotatingClockWidget.h"
#include "HRoundMenuWidget.h"
#include "HJsonTextEdit.h"
#include "HYsaSpecialWidget.h"
#include "HBinaryTreeWidget.h"
#include "HGradientProgressBar.h"
#include "HTextSpotlightWidget.h"
#include "HProgressButton.h"
#include "HSlideButtonGroup.h"
#include <QtCore/QDate>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLayout>

HE_BEGIN_NAMESPACE

void HControlDemoWidget::addYSA()
{
    addTab(tr("友善啊"), tr("图形视图框架"), new HGraphicsDemoWidget);
    addTab(tr("友善啊"), tr("转盘"), new HLotteryTurntableWidget);
    addTab(tr("友善啊"), tr("时钟"), new HRotatingClockWidget);
    addTab(tr("友善啊"), tr("二叉树"), new HBinaryTreeWidget);
    addChat();
    addTimeline();
    addProcessDisplay();
    addPatternLock();
    addGradientProgressBar();
    addYSAWidget();
    addTab(tr("友善啊"), tr("特殊窗体"), new HYsaSpecialWidget);
}

void HControlDemoWidget::addYSAWidget()
{
    auto layout = new QGridLayout;
    auto comboBox = new QComboBox;
    auto view = new HComboBoxTableView(comboBox);
    comboBox->setModel(view->model());
    comboBox->setView(view);
    comboBox->setEditable(true);
    comboBox->lineEdit()->setReadOnly(true);
    comboBox->setStyleSheet("QComboBox { border-radius: 6px; border: 1px solid #00bcd4; padding:6px 10px 6px 10px; font-size:28px; color: #000000; selection-background-color: #00beac; }");
    auto irregularPopup = new HIrregularPopupWidget;
    irregularPopup->setText("黄河之水天上来");
    layout->addWidget(comboBox);
    layout->addWidget(new HOnOffWidget);
    layout->addWidget(new HDiscButton);
    layout->addWidget(new HColorGradientRoundedButton);
    layout->addWidget(new HTimeSlider);
    layout->addWidget(new HColorSelectionRing);
    layout->addWidget(irregularPopup);
    layout->addWidget(new HJsonTextEdit);
    layout->addWidget(new HTextSpotlightWidget);
    layout->addWidget(new HProgressButton);
    layout->addWidget(new HSlideButtonGroup);
    addTab(tr("友善啊"), tr("控件"), layout);
}

void HControlDemoWidget::addChat()
{
    auto widget = new HChatWidget();
    widget->setUserName("张三");
    widget->addPixmap("张三", ":/Resources/image/main.png");
    widget->addPixmap("李四", ":/Resources/image/help.png");
    widget->addChart("张三", "你好呀");
    widget->addChart("李四", "你好");
    widget->addChart("张三", "今天天气不错");
    widget->addChart("李四", "是呀");
    widget->addChart("张三", "明镜高堂悲白发，朝如青丝暮成雪");
    widget->addChart("李四", "黄河之水天上来，奔流到海不复回");
    addTab(tr("友善啊"), tr("聊天记录展示"), widget);
}

void HControlDemoWidget::addTimeline()
{
    auto widget = new HTimelineWidget();
    widget->addInfo(QDate(2021, 10, 1), "国庆节放假");
    widget->addInfo(QDate(2021, 8, 1), "建党百年，伟大征程");
    widget->addInfo(QDate(2021, 5, 1), "劳动节放假");
    widget->addInfo(QDate(2021, 3, 8), "妇女节，女士放假，男士未放假");
    widget->addInfo(QDate(2020, 11, 11), "购物节");
    widget->addInfo(QDate(2020, 12, 26), "圣诞节");
    widget->addInfo(QDate(2020, 4, 1), "愚人节");
    widget->addInfo(QDate(2020, 1, 20), "新冠疫情开始爆发");
    widget->addInfo(QDate(2019, 10, 1), "东风17、东风41亮相");
    auto menu = new HRoundMenuWidget(widget);
    menu->setFixedSize(300, 300);
    addTab(tr("友善啊"), tr("时间轴"), widget);
}

void HControlDemoWidget::addProcessDisplay()
{
    auto widget = new HProcessDisplayWidget;
    widget->setProcess(QStringList() << "确认订单信息" << "提交订单" << "订单完成" << "商品评价" << "追加评论");
    widget->setCurrentStep(2);
    addTab(tr("友善啊"), tr("流程进度展示"), widget);
}

void HControlDemoWidget::addPatternLock()
{
    auto widget = new HPatternLockWidget(4);
    auto btn = new QPushButton("还原");
    auto lineEdit = new QLineEdit;
    auto spinbox = new QSpinBox;
    spinbox->setRange(2,9);
    spinbox->setMinimumWidth(100);
    spinbox->setValue(widget->number());
    auto hb = new QHBoxLayout;
    hb->addWidget(new QLabel("设置的密码："));
    hb->addWidget(lineEdit);
    hb->addWidget(new QLabel("设置行列数："));
    hb->addWidget(spinbox);
    hb->addWidget(btn);
    auto vb = new QVBoxLayout;
    vb->addWidget(widget,5);
    vb->addLayout(hb,1);
    connect(widget, &HPatternLockWidget::passwordChanged, lineEdit, &QLineEdit::setText);
    connect(spinbox, QOverload<int>::of(&QSpinBox::valueChanged), widget, &HPatternLockWidget::setNumber);
    connect(btn, &QPushButton::clicked, widget, &HPatternLockWidget::reset);
    addTab(tr("友善啊"), tr("图案密码锁"), vb);
}

void HControlDemoWidget::addGradientProgressBar()
{
    auto vb = new QVBoxLayout;
    auto bar = new HGradientProgressBar;
    auto slider = new QSlider(Qt::Horizontal);
    slider->setRange(0,100);
    bar->setRange(0,100);
    vb->addWidget(bar);
    vb->addStretch();
    vb->addWidget(slider);
    connect(slider, &QSlider::valueChanged, bar, &QProgressBar::setValue);
    addTab(tr("友善啊"), tr("渐变进度条"), vb);
}

HE_END_NAMESPACE
