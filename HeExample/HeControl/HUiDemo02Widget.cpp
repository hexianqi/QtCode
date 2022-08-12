#include "HUiDemo02Widget.h"
#include "ui_HUiDemo02Widget.h"

HE_BEGIN_NAMESPACE

HUiDemo02Widget::HUiDemo02Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HUiDemo02Widget)
{
    ui->setupUi(this);
    _imageFile << QString(":/Resources/image/main1.jpg")
               << QString(":/Resources/image/main2.jpg")
               << QString(":/Resources/image/main3.jpg")
               << QString(":/Resources/image/main4.jpg")
               << QString(":/Resources/image/main5.jpg");
    updateBackground();
    setWindowTitle("九宫格主界面");
}

HUiDemo02Widget::~HUiDemo02Widget()
{
    delete ui;
}

void HUiDemo02Widget::on_toolButton_01_clicked()
{
    _index = (_index + 1) % _imageFile.count();
    updateBackground();
}

void HUiDemo02Widget::updateBackground()
{
    auto image = _imageFile.at(_index);
    QString qss = QString("QWidget#frm { background-image: url(%1); }").arg(image);
    qss += "QToolButton { color:#E7ECF0; background-color:rgba(0,0,0,0); border-style:none; }";
    this->setStyleSheet(qss);
}

HE_END_NAMESPACE
