#include "HControlDemoWidget_p.h"
#include "HGraphicsDemoWidget.h"
#include "HChatWidget.h"
#include "HComboBoxTableView.h"
#include "HDiscButton.h"
#include "HOnOffWidget.h"
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLineEdit>

HE_BEGIN_NAMESPACE

void HControlDemoWidget::addYSA()
{
    addTab(tr("友善啊"), tr("图形视图框架"), new HGraphicsDemoWidget);
    addTab(tr("友善啊"), tr("开关按钮"), new HOnOffWidget);
    addTab(tr("友善啊"), tr("圆形按钮"), new HDiscButton);
    addTableComboBox();
    addChatWidget();
}

void HControlDemoWidget::addTableComboBox()
{
    auto comboBox = new QComboBox;
    auto view = new HComboBoxTableView(comboBox);
    comboBox->setModel(view->model());
    comboBox->setView(view);
    comboBox->setEditable(true);
    comboBox->lineEdit()->setReadOnly(true);
    comboBox->setStyleSheet("QComboBox { border-radius: 6px; border: 1px solid #00bcd4; padding:6px 10px 6px 10px; font-size:28px; color: #000000; selection-background-color: #00beac; }");
    addTab(tr("友善啊"), tr("表格组合框"), comboBox);
}

void HControlDemoWidget::addChatWidget()
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
    addTab(tr("友善啊"), tr("聊天记录展示控件"), widget);
}

HE_END_NAMESPACE
