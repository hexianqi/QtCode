#include "HUiDemo03Widget.h"
#include "ui_HUiDemo03Widget.h"
#include "HIconFontStyle.h"

HE_BEGIN_NAMESPACE

HUiDemo03Widget::HUiDemo03Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HUiDemo03Widget)
{
    ui->setupUi(this);
    init();
}

HUiDemo03Widget::~HUiDemo03Widget()
{
    delete ui;
}

void HUiDemo03Widget::init()
{
    auto iconSize = 100;
    auto imageSize = QSize(150, 130);
    auto style = new HIconFontStyle(this);
    auto background = QList<QString>() << "#FF3739" << "#1A9FE0" << "#41BB1A" << "#1570A5" << "#FE781F" << "#9B59BB";
    auto text = QList<QString>() << "#FEFEFE" << "#FEFEFE" << "#FEFEFE" << "#FEFEFE" << "#FEFEFE" << "#FEFEFE";
    auto name = QList<QString>() << "访客登记" << "记录查询" << "证件扫描" << "信息打印" << "系统设置" << "系统重启";
    auto icon = QList<int>() << 0xf2ba << 0xf002 << 0xf2c2 << 0xf02f << 0xf013 << 0xf021;
    auto btns = this->findChildren<QToolButton *>();

    for (int i = 0; i < btns.count() && i < 6; i++)
    {
        auto pixmap = style->getPixmap(text.at(i), icon.at(i), iconSize, imageSize);
        auto btn = btns.at(i);
        btn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        btn->setIconSize(imageSize);
        btn->setIcon(pixmap);
        btn->setText(name.at(i));
        btn->setStyleSheet(QString("QToolButton { font:%1px; color:%2; background-color:%3; border:none; border-radius:0px; }")
                               .arg(iconSize / 2).arg(text.at(i)).arg(background.at(i)));
    }

}

HE_END_NAMESPACE
