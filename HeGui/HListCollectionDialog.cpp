#include "HListCollectionDialog_p.h"
#include "ui_HListCollectionDialog.h"
#include "IDataDetailWidget.h"
#include "HePlugin/HPluginHelper.h"
#include <QtCore/QStringListModel>
#include <QtCore/QDebug>

HE_GUI_BEGIN_NAMESPACE

HListCollectionDialog::HListCollectionDialog(QWidget *parent) :
    QDialog(parent),
    d_ptr(new HListCollectionDialogPrivate),
    ui(new Ui::HListCollectionDialog)
{
    ui->setupUi(this);
    init();
}

HListCollectionDialog::~HListCollectionDialog()
{
    qDebug() << __func__;
    delete ui;
}

void HListCollectionDialog::setDataDetailWidget(IDataDetailWidget *p)
{
    d_ptr->widget = p;
    ui->groupBox_2->layout()->addWidget(p);
    connect(d_ptr->widget, &IDataDetailWidget::sourceChanged, this, &HListCollectionDialog::handleSourceChanged);
    d_ptr->widget->start();
}

void HListCollectionDialog::done(int result)
{
    d_ptr->widget->saveData();
    QDialog::done(result);
}

void HListCollectionDialog::on_pushButton_1_clicked()
{
    QString name;
    if (!HPluginHelper::getInputText(this, tr("请输入名称："), name))
        return;
    d_ptr->widget->addItem(name);
}

void HListCollectionDialog::on_pushButton_2_clicked()
{
    if (!d_ptr->currentIndex.isValid())
        return;
    d_ptr->widget->delItem(d_ptr->currentIndex.data().toString());
}

void HListCollectionDialog::on_pushButton_3_clicked()
{
    d_ptr->widget->importFile();
}

void HListCollectionDialog::on_pushButton_4_clicked()
{
    d_ptr->widget->exportFile();
}

void HListCollectionDialog::setCurrentIndex(QModelIndex index)
{
    d_ptr->currentIndex = index;
    d_ptr->widget->setCurrentItem(index.data().toString());
}

void HListCollectionDialog::handleSourceChanged(QStringList names, QString name)
{
    int row = names.indexOf(name);
    d_ptr->model->setStringList(names);
    auto index = d_ptr->model->hasIndex(row, 0) ? d_ptr->model->index(row) : d_ptr->model->index(0);
    ui->listView->setCurrentIndex(index);
    ui->groupBox_2->setEnabled(index.isValid());
    ui->pushButton_1->setEnabled(true);
    ui->pushButton_2->setEnabled(index.isValid());
    ui->pushButton_3->setEnabled(true);
    ui->pushButton_4->setEnabled(true);
}

void HListCollectionDialog::init()
{
    d_ptr->model = new QStringListModel(this);
    ui->listView->setModel(d_ptr->model);
    ui->splitter->setStretchFactor(1, 10);
    connect(ui->listView->selectionModel(), &QItemSelectionModel::currentChanged, this, &HListCollectionDialog::setCurrentIndex);
    setWindowFlags(windowFlags() | Qt::WindowMinMaxButtonsHint);
}

HE_GUI_END_NAMESPACE
