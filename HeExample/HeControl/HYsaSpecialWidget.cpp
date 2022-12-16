#include "HYsaSpecialWidget.h"
#include "ui_HYsaSpecialWidget.h"
#include "HHoverShowWidget.h"
#include "HLineShadowWidget.h"
#include "HRoundShadowWidget.h"
#include <QtWidgets/QGridLayout>

HE_BEGIN_NAMESPACE

HYsaSpecialWidget::HYsaSpecialWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HYsaSpecialWidget)
{
    ui->setupUi(this);
}

HYsaSpecialWidget::~HYsaSpecialWidget()
{
    qDeleteAll(_widgets);
    delete ui;
}

void HYsaSpecialWidget::on_pushButton_1_clicked()
{
    if (!_widgets.contains("悬停显示窗体"))
    {
        auto widget = new HHoverShowWidget;
        widget->setInfoText("测试");
        _widgets["悬停显示窗体"] = widget;
    }
    _widgets["悬停显示窗体"]->show();
}

void HYsaSpecialWidget::on_pushButton_2_clicked()
{
    if (!_widgets.contains("阴影线条窗体"))
        _widgets["阴影线条窗体"] = new HLineShadowWidget;
    _widgets["阴影线条窗体"]->show();
}

void HYsaSpecialWidget::on_pushButton_3_clicked()
{
    if (!_widgets.contains("阴影圆角窗体"))
    {
        auto layout = new QGridLayout;
        auto widget = new HRoundShadowWidget;
        for (int i = 0; i < 5; i++)
        {
            for (int j = 0; j < 5; j++)
            {
                layout->addWidget(new QPushButton("测试"), i, j);
            }
        }
        widget->setCenterWidgetLayout(layout);
        widget->resize(600, 600);
        _widgets["阴影圆角窗体"] = widget;
    }
    _widgets["阴影圆角窗体"]->show();
}

HE_END_NAMESPACE
