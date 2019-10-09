#include "HIconFontWidget.h"
#include "ui_HIconFontWidget.h"
#include <QtGui/QFont>
#include <QtGui/QFontDatabase>

HE_CONTROL_BEGIN_NAMESPACE

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
    // 引入图形字体
    auto fontId = QFontDatabase::addApplicationFont(":/image/fonts/pe-icon-set-weather.ttf");   // 加入字体，并获取字体ID
    auto fontName = QFontDatabase::applicationFontFamilies(fontId).at(0);                       // 获取字体名称
    auto iconFont = QFont(fontName);
    iconFont.setPixelSize(128);                                                                 // 设置字体大小

    ui->label_1->setFont(iconFont);             // 设置字体
    ui->label_1->setText(QChar(0xe901));        // 设置文体
    ui->label_1->setStyleSheet("color:red;");   // 设置颜色

    QPalette palette;
    palette.setColor(QPalette::WindowText, Qt::blue);
    ui->label_2->setFont(iconFont);
    ui->label_2->setText(QChar(0xe903));
    ui->label_2->setPalette(palette);

    ui->label_3->setFont(iconFont);
    ui->label_3->setText(QChar(0xe905));

    ui->label_4->setFont(iconFont);
    ui->label_4->setText(QChar(0xe907));
}

HE_CONTROL_END_NAMESPACE
