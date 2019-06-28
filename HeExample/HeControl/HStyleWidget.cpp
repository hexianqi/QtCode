#include "HStyleWidget_p.h"
#include "ui_HStyleWidget.h"
#include "HStyleFactory.h"
#include "IStyle.h"

HE_CONTROL_BEGIN_NAMESPACE

HStyleWidget::HStyleWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HStyleWidget),
    d_ptr(new HStyleWidgetPrivate)
{
    ui->setupUi(this);
    init();
}

HStyleWidget::~HStyleWidget()
{
    delete ui;
}

void HStyleWidget::init()
{
    d_ptr->factory = new HStyleFactory(this);
    auto style = d_ptr->factory->create("HFaltStyle");
    QStringList list;
    list << style->pushButton()
         << style->lineEdit()
         << style->progressBar()
         << style->slider()
         << style->radioButton()
         << style->checkBox()
         << style->scrollBar();
    this->setStyleSheet(list.join("\n"));
}

HE_CONTROL_END_NAMESPACE
