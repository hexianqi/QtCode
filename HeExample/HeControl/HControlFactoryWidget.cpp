#include "HControlFactoryWidget_p.h"
#include "ui_HControlFactoryWidget.h"
#include "HControlFactory.h"
#include <QtWidgets/QListView>

HE_CONTROL_BEGIN_NAMESPACE

HControlFactoryWidget::HControlFactoryWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HControlFactoryWidget),
    d_ptr(new HControlFactoryWidgetPrivate)
{
    ui->setupUi(this);
    init();
}

HControlFactoryWidget::~HControlFactoryWidget()
{
    delete ui;
}

void HControlFactoryWidget::on_pushButton_clicked()
{
    auto w = d_ptr->factory->createWidget(ui->comboBox->currentText());
    w->show();
}

void HControlFactoryWidget::init()
{
    QStringList qss;
    qss << "QComboBox { min-height: 25px; min-width: 60px; }"
        << "QComboBox QAbstractItemView::item { min-height: 25px; min-width: 60px; }";
    d_ptr->factory = new HControlFactory(this);
    ui->comboBox->setView(new QListView());
    ui->comboBox->addItems(d_ptr->factory->supportedWidgets());
    setStyleSheet(qss.join("\n"));
}

HE_CONTROL_END_NAMESPACE
