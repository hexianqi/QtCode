#include "HAdjustEditWidget_p.h"
#include "ui_HAdjustEditWidget.h"
#include "HAdjustEditDialog.h"
#include "HSimpleTestSetWidget.h"
#include "HeCore/HCore.h"
#include "HeCore/HCoreHelper.h"
#include "HeCore/HAppContext.h"
#include "HeData/IDataFactory.h"
#include "HeData/IAdjust.h"
#include "HeData/IAdjustItem.h"
#include "HePlugin/HPluginHelper.h"
#include "HePlugin/HDoubleSpinBoxDelegate.h"
#include <QtWidgets/QAction>
#include <QtCore/QDebug>

HE_GUI_BEGIN_NAMESPACE

HAdjustEditWidgetPrivate::HAdjustEditWidgetPrivate()
{
    factory = HAppContext::getContextPointer<IDataFactory>("IDataFactory");
    optionals = HAppContext::getContextValue<QStringList>("AdjustOptionals");
}

HAdjustEditWidget::HAdjustEditWidget(QWidget *parent) :
    IDataEditWidget(parent),
    d_ptr(new HAdjustEditWidgetPrivate),
    ui(new Ui::HAdjustEditWidget)
{
    ui->setupUi(this);
    init();
}

HAdjustEditWidget::~HAdjustEditWidget()
{
    qDebug() << __func__;
    delete ui;
}

void HAdjustEditWidget::initialize(QVariantMap /*param*/)
{
}

QString HAdjustEditWidget::typeName()
{
    return "HAdjustEditWidget";
}

IAdjust *HAdjustEditWidget::createData()
{
    return d_ptr->factory->createAdjust("HAdjust");
}

void HAdjustEditWidget::setData(IAdjust *p)
{
    d_ptr->data = p;
    initSelected();
    showData();
}

void HAdjustEditWidget::clearData()
{
    d_ptr->data = nullptr;
    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(0);
}

void HAdjustEditWidget::saveData()
{
    if (d_ptr->data == nullptr)
        return;

    for (int i = 0; i < ui->tableWidget->rowCount(); i++)
    {
        auto key = ui->tableWidget->item(i, 0)->data(Qt::UserRole).toString();
        auto item = d_ptr->data->item(key);
        item->setData("[调整比率]", ui->tableWidget->item(i, 1)->text().toDouble());
        item->setData("[测试值]", ui->tableWidget->item(i, 2)->text().toDouble());
        item->setData("[标准值]", ui->tableWidget->item(i, 3)->text().toDouble());
    }
}

void HAdjustEditWidget::showData()
{
    int r = 0;
    for (auto key : d_ptr->data->keys())
    {
        auto item = ui->tableWidget->item(r, 0);
        item->setData(Qt::UserRole, key);
        item->setFlags(item->flags() & ~Qt::ItemIsEditable);
        ui->tableWidget->setRow(r, d_ptr->data->item(key)->toStringList());
        r++;
    }
}

void HAdjustEditWidget::setEnableEdit(bool b)
{
    d_ptr->actionEdit->setVisible(b);
}

void HAdjustEditWidget::setTestData(QStringList value)
{
    ui->tableWidget->setColumn(2, value);
}

QStringList HAdjustEditWidget::selecteds()
{
    return d_ptr->selecteds;
}

void HAdjustEditWidget::initSelected()
{
    d_ptr->selecteds = d_ptr->data->keys();
    d_ptr->unselecteds = HCoreHelper::unselected(d_ptr->optionals, d_ptr->selecteds);

    auto delegate = new HDoubleSpinBoxDelegate(this);
    delegate->setType(d_ptr->selecteds);
    delegate->setOrientation(Qt::Vertical);
    ui->tableWidget->setItemDelegateForColumn(2, delegate);
    ui->tableWidget->setItemDelegateForColumn(3, delegate);
    ui->tableWidget->setRowCount(d_ptr->selecteds.size());
    ui->pushButton_2->setEnabled(!d_ptr->selecteds.isEmpty());
    ui->pushButton_3->setEnabled(!d_ptr->selecteds.isEmpty());
    ui->pushButton_4->setEnabled(!d_ptr->selecteds.isEmpty());
}

void HAdjustEditWidget::on_pushButton_1_clicked()
{
    QString type;
    if (!HPluginHelper::selectedParameter(this, d_ptr->unselecteds, type))
        return;

    saveData();
    auto item = d_ptr->factory->createAdjustItem("HAdjustItem");
    item->setData("[项类型]", type);
    item->restoreDefault();
    d_ptr->data->insert(type, item);
    initSelected();
    showData();
}

void HAdjustEditWidget::on_pushButton_2_clicked()
{
    QString type;
    if (!HPluginHelper::selectedParameter(this, d_ptr->selecteds, type))
        return;
    saveData();
    d_ptr->data->remove(type);
    initSelected();
    showData();
}

void HAdjustEditWidget::on_pushButton_3_clicked()
{
    d_ptr->data->restoreDefault();
    showData();
}

void HAdjustEditWidget::on_pushButton_4_clicked()
{
    for (int i = 0; i < ui->tableWidget->rowCount(); i++)
    {
        auto d1 = ui->tableWidget->item(i, 2)->text().toDouble();
        auto d2 = ui->tableWidget->item(i, 3)->text().toDouble();
        auto r = qFuzzyIsNull(d1) ? 100 : 100 * d2 / d1;
        ui->tableWidget->item(i, 1)->setText(HCore::toString("[调整比率]", r));
    }
}

void HAdjustEditWidget::init()
{
    d_ptr->actionEdit = new QAction(tr("编辑(&E)..."), this);
    setContextMenuPolicy(Qt::ActionsContextMenu);
    addAction(d_ptr->actionEdit);
    connect(d_ptr->actionEdit, &QAction::triggered, this, &HAdjustEditWidget::openEditDialog);

    auto delegate = new HDoubleSpinBoxDelegate(this);
    delegate->setType("[调整比率]");
    ui->tableWidget->setHorizontalHeaderLabels(QStringList() << tr("项类型") << tr("调整比率") << tr("测试值") << tr("标准值"));
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    ui->tableWidget->setItemDelegateForColumn(1, delegate);
}

void HAdjustEditWidget::openEditDialog()
{
    if (d_ptr->data == nullptr)
        return;
    HAdjustEditDialog dlg;
    dlg.setTestSetWidget(new HSimpleTestSetWidget);
    dlg.setData(d_ptr->data);
    dlg.exec();
}

HE_GUI_END_NAMESPACE
