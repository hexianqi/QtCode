#include "HBase64TranslateWidget.h"
#include "ui_HBase64TranslateWidget.h"

HBase64TranslateWidget::HBase64TranslateWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HBase64TranslateWidget)
{
    ui->setupUi(this);
}

HBase64TranslateWidget::~HBase64TranslateWidget()
{
    delete ui;
}
