#include "HElecCalibrateDialog_p.h"
#include "ui_HElecCalibrateDialog.h"
#include "HeCore/HAppContext.h"
#include "HeCore/HCore.h"
#include "HeData/IConfigManage.h"
#include "HeData/IElecCalibrate.h"
#include "HeData/IElecCalibrateCollection.h"
#include <QtCore/QDebug>

HE_GUI_BEGIN_NAMESPACE

HElecCalibrateDialogPrivate::HElecCalibrateDialogPrivate()
{
    calibrate = HAppContext::getContextPointer<IConfigManage>("IConfigManage")->elecCalibrateCollection();
}

HElecCalibrateDialog::HElecCalibrateDialog(QWidget *parent) :
    QDialog(parent),
    d_ptr(new HElecCalibrateDialogPrivate),
    ui(new Ui::HElecCalibrateDialog)
{
    ui->setupUi(this);
    init();
}

HElecCalibrateDialog::~HElecCalibrateDialog()
{
    qDebug() << __func__;
    delete ui;
}

QTreeWidgetItem *HElecCalibrateDialog::createItem(QString text, int value, QTreeWidgetItem *parent)
{
    auto item = new QTreeWidgetItem(parent);
    item->setText(0, text);
    item->setData(0, Qt::UserRole, value);
    return item;
}

void HElecCalibrateDialog::init()
{
    int flag = 0;
    QTreeWidgetItem *parent;
    IElecCalibrate *item;
    IElecCalibrateItemCollection *collection;

    for (auto key : d_ptr->calibrate->keys())
    {
        item = d_ptr->calibrate->value(key);
        parent = ui->treeWidget->invisibleRootItem();
        if (d_ptr->calibrate->size() > 1)
            parent = createItem(HCore::toCaption(key), flag, parent);
//        collection = item->itemCollection(IElecCalibrate::SourceVoltage);
//        if (collection)

    }
}



HE_GUI_END_NAMESPACE
