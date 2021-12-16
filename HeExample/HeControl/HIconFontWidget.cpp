#include "HIconFontWidget.h"
#include "ui_HIconFontWidget.h"
#include "HIconFontFactory.h"
#include <QtGui/QFont>

HE_BEGIN_NAMESPACE

HIconFontWidget::HIconFontWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HIconFontWidget)
{
    ui->setupUi(this);
    init();
}

HIconFontWidget::~HIconFontWidget()
{
    delete ui;
}

void HIconFontWidget::init()
{
    auto factory = new HIconFontFactory(this);
    auto font = factory->createFont("pe-icon-set-weather");
    font.setPixelSize(128);             // 设置字体大小

    QPalette palette;
    palette.setColor(QPalette::WindowText, Qt::blue);

    ui->label_1->setFont(font);                 // 设置字体
    ui->label_1->setText(QChar(0xe901));        // 设置文体
    ui->label_1->setStyleSheet("color:red;");   // 设置颜色
    ui->label_2->setFont(font);
    ui->label_2->setText(QChar(0xe903));
    ui->label_2->setPalette(palette);
    ui->label_3->setFont(font);
    ui->label_3->setText(QChar(0xe905));
    ui->label_4->setFont(font);
    ui->label_4->setText(QChar(0xe907));
}

HE_END_NAMESPACE
