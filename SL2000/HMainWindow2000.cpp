#include "HMainWindow2000_p.h"
#include "HBuilder2000.h"
#include "HeData/IConfigManage.h"
#include "HeController/IModel.h"
#include "HeGui/ITestWidget.h"
#include "HeGui/HSpecCalibrateDialog.h"
#include <QtWidgets/QMenuBar>
#include <QtCore/QDebug>

HE_DATA_USE_NAMESPACE

HMainWindow2000Private::HMainWindow2000Private(HMainWindow2000 *q) :
    HMainWindowPrivate(q)
{
}

HMainWindow2000::HMainWindow2000(QWidget *parent, const HCallorHelper &helper) :
    HAbstractMainWindow(*new HMainWindow2000Private(this), helper, parent)
{
}

HMainWindow2000::~HMainWindow2000()
{
    qDebug() << __func__;
}

void HMainWindow2000::initImportExport()
{
    Q_D(HMainWindow2000);
    HAbstractMainWindow::initImportExport();
    d->importExport.insert(tr("1.光谱定标数据(&S)..."),           ConfigContainType::CCT_Spec);
}

void HMainWindow2000::initBuilder()
{
    Q_D(HMainWindow2000);
    d->builder = new HBuilder2000(this);
    d->builder->buildAll();
}

void HMainWindow2000::createAction()
{
    HAbstractMainWindow::createAction();
    Q_D(HMainWindow2000);
    d->actionCalibrateSpectrum = new QAction(tr("光谱定标(&S)..."), this);
    connect(d->actionCalibrateSpectrum, &QAction::triggered, this, &HMainWindow2000::openCalibrateSpectrumDialog);
}

void HMainWindow2000::createMenu()
{
    Q_D(HMainWindow2000);
    HAbstractMainWindow::createMenu();
    d->menuCalibrate = new QMenu(tr("定标(&C)"));
    d->menuCalibrate->addAction(d->actionCalibrateSpectrum);
}

void HMainWindow2000::initMenu()
{
    HAbstractMainWindow::initMenu();
    Q_D(HMainWindow2000);
    menuBar()->insertMenu(d->actionSeparator, d->menuCalibrate);
}

bool HMainWindow2000::openCalibrateDlg(QDialog *dlg)
{
    Q_D(HMainWindow2000);
    d->testWidget->stop();
    auto result = dlg->exec();
    d->testWidget->start();
    return result == QDialog::Accepted;
}

void HMainWindow2000::openCalibrateSpectrumDialog()
{
    Q_D(HMainWindow2000);
    HSpecCalibrateDialog dlg;
    openCalibrateDlg(&dlg);
    d->model->addAction(ACT_RESET_SPECTRUM);
}
