#include "HRunTimeDemoWidget.h"
#include "ui_HRunTimeDemoWidget.h"
#include "HRunTimeService.h"
#include "ILogFile.h"

HE_BEGIN_NAMESPACE

HRunTimeDemoWidget::HRunTimeDemoWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HRunTimeDemoWidget)
{
    ui->setupUi(this);
    init();
}

HRunTimeDemoWidget::~HRunTimeDemoWidget()
{
    delete ui;
}

void HRunTimeDemoWidget::on_checkBox_clicked(bool b)
{
    if (b)
        service->start();
    else
        service->stop();
}

void HRunTimeDemoWidget::on_pushButton_1_clicked()
{
    service->initLog();
    service->appendLog();
}

void HRunTimeDemoWidget::on_pushButton_2_clicked()
{
    service->saveLog();
}

void HRunTimeDemoWidget::on_pushButton_3_clicked()
{
    refresh();
}

void HRunTimeDemoWidget::refresh()
{
    ui->textEdit->setText(service->file()->readAll());
}

void HRunTimeDemoWidget::init()
{
    service = HRunTimeService::instance();
    connect(service, &HRunTimeService::dataChanged, this, &HRunTimeDemoWidget::refresh);
}


HE_END_NAMESPACE
