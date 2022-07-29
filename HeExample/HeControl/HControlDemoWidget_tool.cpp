#include "HControlDemoWidget_p.h"
#include "HBase64ConvertWidget.h"
#include "HChineseConvert.h"
#include "HCodeCountWidget.h"
#include "HEmailWidget.h"
#include "HNetworkWidget.h"
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>



#include "HPngAmend.h"
#include "HSerialPortWidget.h"


HE_BEGIN_NAMESPACE

void HControlDemoWidget::addTool()
{
    addChineseConvert();
    addTab(tr("工具"), new HBase64ConvertWidget);
    addTab(tr("工具"), new HCodeCountWidget);
    addTab(tr("工具"), new HEmailWidget);
    addTab(tr("工具"), new HNetworkWidget);

    addTab(tr("工具"), new HPngAmend);
    addTab(tr("工具"), new HSerialPortWidget);
}

void HControlDemoWidget::addChineseConvert()
{
    auto button1 = new QPushButton(tr("转全拼"));
    auto button2 = new QPushButton(tr("转简拼"));
    auto lineEdit1 = new QLineEdit(tr("测试文字"));
    auto lineEdit2 = new QLineEdit;
    connect(button1, &QPushButton::clicked, [=] { lineEdit2->setText(HChineseConvert::instance()->toPingYin(lineEdit1->text())); });
    connect(button2, &QPushButton::clicked, [=] { lineEdit2->setText(HChineseConvert::instance()->toJianPin(lineEdit1->text())); });
    auto layout = new QGridLayout;
    layout->addWidget(new QLabel(tr("汉字：")), 0, 0);
    layout->addWidget(lineEdit1, 0, 1);
    layout->addWidget(button1, 0, 2);
    layout->addWidget(new QLabel(tr("结果：")), 1, 0);
    layout->addWidget(lineEdit2, 1, 1);
    layout->addWidget(button2, 1, 2);
    layout->addItem(new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding), 2, 0);
    addTab(tr("工具"), tr("汉字转拼音"), layout);
}

HE_END_NAMESPACE
