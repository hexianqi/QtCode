#include "HMainWindowSpec_p.h"
#include "HBuilderSpec.h"
#include "HeCore/HAppContext.h"
#include "HeData/IConfigManage.h"
#include "HeData/ISpecCalibrate.h"
#include "HeController/IModel.h"
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QMenu>
#include <QtWidgets/QFileDialog>
#include <QtCore/QDebug>

HE_DATA_USE_NAMESPACE

HMainWindowSpec::HMainWindowSpec(QWidget *parent, const HCallorHelper &helper) :
    HAbstractMainWindow(*new HMainWindowSpecPrivate(this), helper, parent)
{
}

HMainWindowSpec::~HMainWindowSpec()
{
    qDebug() << __func__;
}

void HMainWindowSpec::initImportExport()
{
    Q_D(HMainWindowSpec);
    HAbstractMainWindow::initImportExport();
    d->importExport.insert(tr("1.光谱定标数据(&S)..."),           IConfigManage::ContainSpec);
}

void HMainWindowSpec::initBuilder()
{
    Q_D(HMainWindowSpec);
    d->builder = new HBuilderSpec(this);
    d->builder->buildAll();

    d->configManage = HAppContext::getContextPointer<IConfigManage>("IConfigManage");

    d->actionSetRam = new QAction(tr("写入数据到设备(&S)"), this);
    d->actionGetRam = new QAction(tr("从设备读取数据(&G)"), this);
    d->actionImportCurve = new QAction(tr("导入标准曲线(&I)"), this);
    d->actionExportCurve = new QAction(tr("导出标准曲线(&E)"), this);
    connect(d->actionSetRam, &QAction::triggered, this, [=]{ d->model->addAction(ACT_SET_RAM); });
    connect(d->actionGetRam, &QAction::triggered, this, [=]{ d->model->addAction(ACT_GET_RAM); });
    connect(d->actionImportCurve, &QAction::triggered, this, &HMainWindowSpec::importCurve);
    connect(d->actionExportCurve, &QAction::triggered, this, &HMainWindowSpec::exportCurve);

    auto menu = new QMenu(tr("设备配置(&T)"));
    menu->addAction(d->actionSetRam);
    menu->addAction(d->actionGetRam);
    menu->addAction(d->actionImportCurve);
    menu->addAction(d->actionExportCurve);

    insertMenu(menu);
}

void HMainWindowSpec::importCurve()
{
    Q_D(HMainWindowSpec);
    auto fileName = QFileDialog::getOpenFileName(this, tr("导入"), ".", "*.dat");
    if (fileName.isEmpty())
        return;
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    int i,n;
    double t;
    QString str;
    QVector<double> curve;
    QTextStream s(&file);
    s >> n >> str;
    if (n < 2000)
    {
        QMessageBox::warning(this, "", tr("\n无效标准曲线数据！\n"));
        file.close();
        return;
    }
    for (i = 0; i < n; i++)
    {
        s >> t;
        curve << t;
    }
    file.close();
    d->configManage->specCalibrate("1")->setStdCurve(curve);
    QMessageBox::information(this, "", tr("\n导入成功！\n"));
}

void HMainWindowSpec::exportCurve()
{
    Q_D(HMainWindowSpec);
    auto fileName = QFileDialog::getSaveFileName(this, tr("导出"), ".", "*.dat");
    if (fileName.isEmpty())
        return;
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    auto curve = d->configManage->specCalibrate("1")->stdCurve();
    if (curve.size() < 2000)
    {
        QMessageBox::warning(this, "", tr("\n无效标准曲线数据！\n"));
        return;
    }
    QTextStream s(&file);
    s << curve.size() << "\t1" << endl;
    for (auto v : curve)
        s << QString::number(v, 'f', 1) << endl;
    file.close();
    QMessageBox::information(this, "", tr("\n导出成功！\n"));
}

