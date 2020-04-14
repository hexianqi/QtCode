#include "HSqlFindDialog_p.h"
#include "ui_HSqlFindDialog.h"
#include "HSql.h"
#include <QtCore/QDebug>
#include <QtCore/QStringListModel>

HE_SQL_BEGIN_NAMESPACE

HSqlFindDialog::HSqlFindDialog(const QStringList &fields, const QString &filter, QWidget *parent) :
    QDialog(parent),
    d_ptr(new HSqlFindDialogPrivate),
    ui(new Ui::HSqlFindDialog)
{
    ui->setupUi(this);
    d_ptr->fields = fields;
    d_ptr->compares = QStringList() << " > " << " >= " << " = " << " <= " << " < " ;
    d_ptr->filter = filter;
    init();
}

HSqlFindDialog::~HSqlFindDialog()
{
    qDebug() << __func__;
    delete ui;
}

QString HSqlFindDialog::filter() const
{
    return d_ptr->filter;
}

void HSqlFindDialog::done(int result)
{
    if (result == QDialog::Accepted)
        d_ptr->filter = d_ptr->model->stringList().join(" AND ");
    QDialog::done(result);
}

void HSqlFindDialog::on_pushButton_1_clicked()
{
    auto text = ui->lineEdit_1->text();
    if (text.isEmpty())
        return;
    auto row = d_ptr->model->rowCount();
    auto value = d_ptr->fields.at(ui->comboBox_1->currentIndex()) + d_ptr->compares.at(ui->comboBox_2->currentIndex()) + "'" + text + "'";
    d_ptr->model->insertRow(row);
    d_ptr->model->setData(d_ptr->model->index(row), value);
}

void HSqlFindDialog::on_pushButton_2_clicked()
{
    d_ptr->model->removeRow(ui->listView->currentIndex().row());
}

void HSqlFindDialog::on_pushButton_3_clicked()
{
    d_ptr->model->removeRows(0, d_ptr->model->rowCount());
}

void HSqlFindDialog::init()
{
    d_ptr->model = new QStringListModel(this);
    d_ptr->model->setStringList(d_ptr->filter.split(" AND ", QString::SkipEmptyParts));
    ui->listView->setModel(d_ptr->model);
    ui->comboBox_1->addItems(HSql::toCaption(d_ptr->fields));
    ui->comboBox_2->addItems(d_ptr->compares);
    ui->comboBox_2->setCurrentIndex(2);
}

HE_SQL_END_NAMESPACE
