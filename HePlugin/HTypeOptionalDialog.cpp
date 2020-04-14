#include "HTypeOptionalDialog_p.h"
#include "ui_HTypeOptionalDialog.h"
#include "HeCore/HCore.h"
#include "HeCore/HCoreHelper.h"

HE_CORE_USE_NAMESPACE

HTypeOptionalDialog::HTypeOptionalDialog(const QStringList &selected, const QStringList &optional, QWidget *parent) :
    QDialog(parent),
    d_ptr(new HTypeOptionalDialogPrivate),
    ui(new Ui::HTypeOptionalDialog)
{
    ui->setupUi(this);
    d_ptr->optionals = optional;
    d_ptr->selecteds = selected;
    d_ptr->unselecteds = HCoreHelper::unselected(optional, selected);
    showData();
}

HTypeOptionalDialog::~HTypeOptionalDialog()
{
    delete ui;
}

QStringList HTypeOptionalDialog::selected()
{
    return d_ptr->selecteds;
}

void HTypeOptionalDialog::on_toolButton_1_clicked()
{
    if (ui->listWidget_2->currentItem())
    {
        auto item = ui->listWidget_2->currentItem()->clone();
        ui->listWidget_1->insertItem(ui->listWidget_1->currentRow()+1, item);
        ui->listWidget_1->setCurrentItem(item);
        delete ui->listWidget_2->currentItem();
    }
}

void HTypeOptionalDialog::on_toolButton_2_clicked()
{
    if (ui->listWidget_1->currentItem())
    {
        auto item = ui->listWidget_1->currentItem()->clone();
        ui->listWidget_2->insertItem(ui->listWidget_2->currentRow()+1, item);
        ui->listWidget_2->setCurrentItem(item);
        delete ui->listWidget_1->currentItem();
    }
}

void HTypeOptionalDialog::on_toolButton_3_clicked()
{
    if (ui->listWidget_2->currentItem())
    {
        auto item = ui->listWidget_2->currentItem()->clone();
        ui->listWidget_2->insertItem(ui->listWidget_2->currentRow()-1, item);
        delete ui->listWidget_2->currentItem();
        ui->listWidget_2->setCurrentItem(item);
    }
}

void HTypeOptionalDialog::on_toolButton_4_clicked()
{
    if (ui->listWidget_2->currentItem())
    {
        auto item = ui->listWidget_2->currentItem()->clone();
        delete ui->listWidget_2->currentItem();
        ui->listWidget_2->insertItem(ui->listWidget_2->currentRow()+1, item);
        ui->listWidget_2->setCurrentItem(item);
    }
}

void HTypeOptionalDialog::done(int result)
{
    if (result == QDialog::Accepted)
        saveData();
    QDialog::done(result);
}

void HTypeOptionalDialog::showData()
{
    for (const auto &t : d_ptr->unselecteds)
    {
        auto item = new QListWidgetItem;
        item->setData(Qt::UserRole, t);
        item->setData(Qt::DisplayRole, HCore::toCaption(t));
        ui->listWidget_1->addItem(item);
    }
    for (const auto &t : d_ptr->selecteds)
    {
        auto item = new QListWidgetItem;
        item->setData(Qt::UserRole, t);
        item->setData(Qt::DisplayRole, HCore::toCaption(t));
        ui->listWidget_2->addItem(item);
    }
}

void HTypeOptionalDialog::saveData()
{
    d_ptr->selecteds.clear();
    for (int i = 0; i< ui->listWidget_2->count(); i++)
        d_ptr->selecteds << ui->listWidget_2->item(i)->data(Qt::UserRole).toString();
}
