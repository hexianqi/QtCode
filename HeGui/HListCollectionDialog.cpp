#include "HListCollectionDialog_p.h"
#include "ui_HListCollectionDialog.h"
#include "IItemDetailWidget.h"
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

void HListCollectionDialog::setItemDetailWidget(IItemDetailWidget *p)
{
    d_ptr->itemWidget = p;
    ui->groupBox_2->layout()->addWidget(p);
    connect(d_ptr->itemWidget, &IItemDetailWidget::sourceChanged, this, &HListCollectionDialog::handleSourceChanged);
    d_ptr->itemWidget->start();
}

void HListCollectionDialog::on_pushButton_1_clicked()
{
    QString name;
    if (!HPluginHelper::getInputText(this, tr("请输入名称："), name))
        return;
    d_ptr->itemWidget->addItem(name);
}

void HListCollectionDialog::on_pushButton_2_clicked()
{
    if (!d_ptr->currentIndex.isValid())
        return;
    d_ptr->itemWidget->delItem(d_ptr->currentIndex.data().toString());
}

void HListCollectionDialog::on_pushButton_3_clicked()
{
    d_ptr->itemWidget->importFile();
}

void HListCollectionDialog::on_pushButton_4_clicked()
{
    d_ptr->itemWidget->exportFile();
}

void HListCollectionDialog::setCurrentIndex(QModelIndex index)
{
    d_ptr->currentIndex = index;
    auto name = index.isValid() ? index.data().toString() : "";
    d_ptr->itemWidget->setCurrentItem(name);
}

void HListCollectionDialog::handleSourceChanged(QStringList names, QString name)
{
    int row = names.indexOf(name);
    d_ptr->model->setStringList(names);
    auto index = d_ptr->model->hasIndex(row, 0) ? d_ptr->model->index(row) : d_ptr->model->index(0);
    ui->listView->setCurrentIndex(index);
    ui->groupBox_2->setEnabled(index.isValid());
    ui->pushButton_2->setEnabled(index.isValid());
}

void HListCollectionDialog::init()
{
    d_ptr->model = new QStringListModel(this);
    ui->listView->setModel(d_ptr->model);
    ui->splitter->setStretchFactor(1, 1);
    connect(ui->listView->selectionModel(), &QItemSelectionModel::currentChanged, this, &HListCollectionDialog::setCurrentIndex);
    setWindowFlags(windowFlags() | Qt::WindowMinMaxButtonsHint);
}

HE_GUI_END_NAMESPACE
