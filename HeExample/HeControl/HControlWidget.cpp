#include "HControlWidget_p.h"
#include "ui_HControlWidget.h"
#include "HControlFactory.h"

HE_CONTROL_BEGIN_NAMESPACE

HControlWidget::HControlWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HControlWidget),
    d_ptr(new HControlWidgetPrivate)
{
    ui->setupUi(this);
    init();
}

HControlWidget::~HControlWidget()
{
    delete ui;
}

void HControlWidget::on_pushButton_clicked()
{
    auto w = d_ptr->factory->createWidget(ui->comboBox->currentText());
    w->show();
}

void HControlWidget::init()
{
    d_ptr->factory = new HControlFactory(this);
    ui->comboBox->addItems(d_ptr->factory->keys());
}

HE_CONTROL_END_NAMESPACE
