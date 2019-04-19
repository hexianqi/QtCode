#include "HListCollectionDialog_p.h"
#include "ui_HListCollectionDialog.h"
#include "IItemDetailWidget.h"
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

HListCollectionDialog::HListCollectionDialog(HListCollectionDialogPrivate &p, QWidget *parent) :
    QDialog(parent),
    d_ptr(&p),
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
    connect(ui->pushButton_01, &QPushButton::click, d_ptr->itemWidget, &IItemDetailWidget::addItem);
    connect(ui->pushButton_02, &QPushButton::click, d_ptr->itemWidget, &IItemDetailWidget::delItem);
    connect(ui->pushButton_03, &QPushButton::click, d_ptr->itemWidget, &IItemDetailWidget::importFile);
    connect(ui->pushButton_04, &QPushButton::click, d_ptr->itemWidget, &IItemDetailWidget::exportFile);
    connect(d_ptr->itemWidget, &IItemDetailWidget::sourceChanged, this, &HListCollectionDialog::handleSourceChanged);
    d_ptr->itemWidget->start();
}

void HListCollectionDialog::setCurrentIndex(QModelIndex index)
{
    if (d_ptr->currentIndex == index)
        return;
    d_ptr->currentIndex = index;
    d_ptr->itemWidget->setCurrentItem(index.data().toString());
}

void HListCollectionDialog::handleSourceChanged(QStringList names, QString name)
{
    int row = names.indexOf(name);
    d_ptr->model->setStringList(names);
    d_ptr->currentIndex = d_ptr->model->hasIndex(row, 0) ? d_ptr->model->index(row) : d_ptr->model->index(d_ptr->model->rowCount() - 1);
    ui->listView->setCurrentIndex(d_ptr->currentIndex);
    ui->groupBox_2->setEnabled(d_ptr->currentIndex.isValid());
    ui->pushButton_02->setEnabled(d_ptr->currentIndex.isValid());
}

void HListCollectionDialog::init()
{
    d_ptr->model = new QStringListModel(this);
    ui->listView->setModel(d_ptr->model);
    ui->splitter->setStretchFactor(1, 1);
    connect(ui->listView->selectionModel(), &QItemSelectionModel::currentChanged, this, &HListCollectionDialog::setCurrentIndex);
    setWindowFlags(Qt::Dialog | Qt::WindowMinMaxButtonsHint);
}

HE_GUI_END_NAMESPACE
