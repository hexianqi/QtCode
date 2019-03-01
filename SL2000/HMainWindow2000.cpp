#include "HMainWindow2000_p.h"
#include "HeData/IConfigManage.h"
#include "HeController/IModel.h"
#include <QMenuBar>
#include <QDebug>

HMainWindow2000Private::HMainWindow2000Private(HMainWindow2000 *q)
    : HMainWindowPrivate(q)
{
}

HMainWindow2000::HMainWindow2000(QWidget *parent)
    : HMainWindow(*new HMainWindow2000Private(this), parent)
{
    init();
}

HMainWindow2000::HMainWindow2000(HMainWindow2000Private &p, QWidget *parent)
    : HMainWindow(p, parent)
{
    init();
}

HMainWindow2000::~HMainWindow2000()
{
    qDebug() << __func__;
}

void HMainWindow2000::initImportExport()
{
    Q_D(HMainWindow2000);
    HMainWindow::initImportExport();
    d->importExport.insert(tr("1.光谱定标数据(&S)..."),           ConfigContainType::CCT_Spec);
}

void HMainWindow2000::createAction()
{
    Q_D(HMainWindow2000);
    HMainWindow2000::createAction();
    d->actionCalibrateSpectrum = new QAction(tr("光谱定标(&S)..."), this);
}

void HMainWindow2000::createMenu()
{
    Q_D(HMainWindow2000);
    HMainWindow2000::createMenu();
    d->menuCalibrate = new QMenu(tr("定标(&C)"));
    d->menuCalibrate->addAction(d->actionCalibrateSpectrum);
}

void HMainWindow2000::createConnect()
{
    Q_D(HMainWindow2000);
    HMainWindow2000::createConnect();
    connect(d->actionCalibrateSpectrum, &QAction::triggered, this, openCalibrateSpectrumDialog);
}

void HMainWindow2000::initMenu()
{
    Q_D(HMainWindow2000);
    HMainWindow2000::initMenu();
    menuBar()->insertMenu(d->actionSeparator, d->menuCalibrate);
}

bool HMainWindow2000::openCalibrateDlg(QDialog *dlg, bool message)
{
//    int result;

//    if (m_pWidget != 0)
//        m_pWidget->pause();
//    result = dlg->exec();
//    if (m_pWidget != 0)
//        m_pWidget->start();
//    if (result == QDialog::Accepted && message)
//        QMessageBox::information(this, tr("设置"), tr("\n设置完成！\n"), QMessageBox::Yes);
//    return result == QDialog::Accepted;
}

void HMainWindow2000::openCalibrateSpectrumDialog()
{
    Q_D(HMainWindow2000);
    d->model->addAction(ACT_RESET_SPECTRUM);
//    FSpectrumCalibrateDialog dlg(m_pInterface, this);
//    if (openCalibrateDlg(&dlg))
//        m_pInterface->addAction(ACT_RESET_SPECTRUM);
}
