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

QString HSelectDialog::currentText() const
{
    return ui->comboBox_1->currentText();
}

QVariant HSelectDialog::currentData() const
{
    return ui->comboBox_1->currentData();
}

void HSelectDialog::setLabelText(const QString &value)
{
    ui->label_001->setText(value);
}

void HSelectDialog::setOptionals(const QStringList &value)
{
    ui->comboBox_1->addItems(value);
}

void HSelectDialog::setOptionals(const QVariantMap &value)
{
    for (auto i = value.begin(); i != value.end(); i++)
        ui->comboBox_1->addItem(i.key(), i.value());
}

void HSelectDialog::setCurrentText(const QString &value)
{
    ui->comboBox_1->setCurrentText(value);
}

void HSelectDialog::setCurrentIndex(int index)
{
    ui->comboBox_1->setCurrentIndex(index);
}
