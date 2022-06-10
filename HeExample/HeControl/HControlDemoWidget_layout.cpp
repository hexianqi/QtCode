#include "HControlDemoWidget_p.h"
#include "HBorderLayout.h"
#include "HCardLayout.h"
#include "HFlowLayout.h"
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

HE_BEGIN_NAMESPACE

void HControlDemoWidget::addLayout()
{
    addBorderLayout();
    addCardLayout();
    addFlowLayout();
}

void HControlDemoWidget::addBorderLayout()
{
    auto layout = new HBorderLayout;
    layout->addWidget(new QPushButton("West 1"),   HBorderLayout::West);
    layout->addWidget(new QPushButton("West 2"),   HBorderLayout::West);
    layout->addWidget(new QPushButton("North 1"),  HBorderLayout::North);
    layout->addWidget(new QPushButton("North 2"),  HBorderLayout::North);
    layout->addWidget(new QPushButton("South 1"),  HBorderLayout::South);
    layout->addWidget(new QPushButton("South 2"),  HBorderLayout::South);
    layout->addWidget(new QPushButton("East 1"),   HBorderLayout::East);
    layout->addWidget(new QPushButton("East 2"),   HBorderLayout::East);
    layout->addWidget(new QPushButton("Center"),   HBorderLayout::Center);
    addTab(tr("布局"), tr("边界布局"), layout);
}

void HControlDemoWidget::addCardLayout()
{
    auto layout = new HCardLayout;
    for (int i = 0; i < 10; i++)
        layout->addWidget(new QLabel(QString("Card %1").arg(i + 1)));
    addTab(tr("布局"), tr("卡片布局"), layout);
}

void HControlDemoWidget::addFlowLayout()
{
    auto layout = new HFlowLayout;
    for (int i = 0; i < 100; i++)
        layout->addWidget(new QLabel(QString("Card %1").arg(i + 1)));
    addTab(tr("布局"), tr("流程布局"), layout);
}

HE_END_NAMESPACE
