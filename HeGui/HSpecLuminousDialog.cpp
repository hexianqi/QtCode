#include "HSpecLuminousDialog_p.h"
#include "ui_HSpecLuminousDialog.h"
#include "HeCore/HCore.h"
#include "HePlugin/HPluginHelper.h"
#include "HePlugin/HDoubleSpinBoxDelegate.h"
#include "HeData/HSpecLuminous.h"
#include <QtWidgets/QInputDialog>
#include <QtCore/QDebug>

HE_GUI_BEGIN_NAMESPACE

HSpecLuminousDialog::HSpecLuminousDialog(QWidget *parent) :
    QDialog(parent),
    d_ptr(new HSpecLuminousDialogPrivate),
    ui(new Ui::HSpecLuminousDialog)
{
    ui->setupUi(this);
    init();
}

HSpecLuminousDialog::~HSpecLuminousDialog()
{
    qDebug() << __func__;
    delete ui;
}

void HSpecLuminousDialog::setData(HSpecLuminous *p)
{
    d_ptr->data = p;
    showData();
}

void HSpecLuminousDialog::on_pushButton_11_clicked()
{
    QString text;
    if (!HPluginHelper::getInputText(this, tr("请输入名称："), text) || text.isEmpty())
        return;

    ui->tableWidget_11->insertRow(ui->tableWidget_11->rowCount(), QStringList() << text << "0.00");
    ui->comboBox->addItem(text);
    d_ptr->keys << text;
}

void HSpecLuminousDialog::on_pushButton_12_clicked()
{
    bool ok;
    auto item = QInputDialog::getItem(this, "", tr("请选择参数："), d_ptr->keys, 0, false, &ok);
    if (!ok || item.isEmpty())
        return;
    auto index = d_ptr->keys.indexOf(item);
    if (index < 0)
        return;
    ui->tableWidget_11->removeRow(index);
    ui->comboBox->removeItem(index);
    d_ptr->keys.removeAt(index);
}

void HSpecLuminousDialog::done(int result)
{
    if (result == QDialog::Accepted)
        saveData();
    QDialog::done(result);
}

void HSpecLuminousDialog::showData()
{
    QList<QStringList> list;
    auto a = d_ptr->data->selfAbsorption();
    for (auto i = a.begin(); i != a.end(); i++)
        list.append(QStringList() << i.key() << HCore::toString("[自吸收系数]", i.value()));

    d_ptr->keys = a.keys();
    ui->checkBox->setChecked(d_ptr->data->data("[自吸收启用]").toBool());
    ui->comboBox->addItems(d_ptr->keys);
    ui->comboBox->setCurrentText(d_ptr->data->data("[自吸收选项]").toString());
    ui->tableWidget_11->setRowCount(list.size());
    for (int i = 0; i < list.size(); i++)
        ui->tableWidget_11->setRow(i, list[i]);
}

void HSpecLuminousDialog::saveData()
{
    QMap<QString, double> a;
    for (int i = 0; i < ui->tableWidget_11->rowCount(); i++)
        a.insert(ui->tableWidget_11->item(i, 0)->text(), ui->tableWidget_11->item(i, 1)->text().toDouble());
    d_ptr->data->setData("[自吸收启用]", ui->checkBox->isChecked());
    d_ptr->data->setData("[自吸收选项]", ui->comboBox->currentText());
    d_ptr->data->setSelfAbsorption(a);
}

void HSpecLuminousDialog::init()
{
    auto delegate = new HDoubleSpinBoxDelegate(this);
    delegate->setType("[自吸收系数]");
    ui->tableWidget_11->setItemDelegateForColumn(1, delegate);
    ui->tableWidget_11->setHorizontalHeaderLabels(QStringList() << tr("名称") << tr("自吸收系数"));
    setWindowTitle(tr("光通量自吸收配置"));
}

HE_GUI_END_NAMESPACE
