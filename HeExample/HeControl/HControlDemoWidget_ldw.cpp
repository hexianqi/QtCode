#include "HControlDemoWidget_p.h"

#include "HFlatStyle.h"

#include "HImageCalendar.h"
#include "HLunarCalendarWidget.h"


#include <QtWidgets/QLabel>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGridLayout>

HE_BEGIN_NAMESPACE

void HControlDemoWidget::addLiuDianWu()
{
    addCalendar();
    addLunarCalendar();
}

void HControlDemoWidget::addCalendar()
{
    addTab(tr("ludianwu"), new HImageCalendar);
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

HE_END_NAMESPACE
