#include "HSelectDialog.h"
#include "ui_HSelectDialog.h"

HSelectDialog::HSelectDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HSelectDialog)
{
    ui->setupUi(this);
}

HSelectDialog::~HSelectDialog()
{
    delete ui;
}

void HSelectDialog::setLabelText(QString value)
{
    ui->label_001->setText(value);
}

void HSelectDialog::setOptionals(QStringList value)
{
    ui->comboBox_1->addItems(value);
}

void HSelectDialog::setSelected(QString value)
{
    ui->comboBox_1->setCurrentText(value);
}

QString HSelectDialog::selected()
{
    return ui->comboBox_1->currentText();
}
