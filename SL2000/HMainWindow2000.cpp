#include "HMainWindow2000_p.h"
#include "HeData/IConfigManage.h"
#include "HeController/IModel.h"
#include <QMenuBar>
#include <QDebug>

HMainWindow2000Private::HMainWindow2000Private(HMainWindow2000 *q)
    : HMainWindowPrivate(q)
{
}

HMainWindow2000::HMainWindow2000(QWidget *parent, const HCallorHelper &helper)
    : HAbstractMainWindow(*new HMainWindow2000Private(this), helper, parent)
{
}

HMainWindow2000::HMainWindow2000(HMainWindow2000Private &p, const HCallorHelper &helper, QWidget *parent)
    : HAbstractMainWindow(p, helper, parent)
{
}

HMainWindow2000::~HMainWindow2000()
{
    qDebug() << __func__;
}

void HMainWindow2000::initImportExport()
{
    HAbstractMainWindow::initImportExport();
    Q_D(HMainWindow2000);
    d->importExport.insert(tr("1.光谱定标数据(&S)..."),           ConfigContainType::CCT_Spec);
}

void HMainWindow2000::createAction()
{
    HAbstractMainWindow::createAction();
    Q_D(HMainWindow2000);
    d->actionCalibrateSpectrum = new QAction(tr("光谱定标(&S)..."), this);
}

void HMainWindow2000::createMenu()
{
    HAbstractMainWindow::createMenu();
    Q_D(HMainWindow2000);
    d->menuCalibrate = new QMenu(tr("定标(&C)"));
    d->menuCalibrate->addAction(d->actionCalibrateSpectrum);
}

void HMainWindow2000::createConnect()
{
    HAbstractMainWindow::createConnect();
    Q_D(HMainWindow2000);
    connect(d->actionCalibrateSpectrum, &QAction::triggered, this, &HMainWindow2000::openCalibrateSpectrumDialog);
}

void HMainWindow2000::initMenu()
{
    HAbstractMainWindow::initMenu();
    Q_D(HMainWindow2000);
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
