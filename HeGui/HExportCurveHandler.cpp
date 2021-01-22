#include "HExportCurveHandler_p.h"
#include "IMainWindow.h"
#include "HeData/IConfigManage.h"
#include "HeData/ISpecCalibrate.h"
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QMessageBox>
#include <QtCore/QDebug>

HE_GUI_BEGIN_NAMESPACE

HExportCurveHandler::HExportCurveHandler(QObject *parent) :
    HAbstractConfigHandler(*new HExportCurveHandlerPrivate, parent)
{
}

HExportCurveHandler::~HExportCurveHandler()
{
    qDebug() << __func__;
}

void HExportCurveHandler::initialize(QVariantMap /*param*/)
{

}

QString HExportCurveHandler::typeName()
{
    return "HExportCurveHandler";
}

void HExportCurveHandler::execute(QObject */*sender*/, QVariantMap /*param*/)
{
    Q_D(HExportCurveHandler);
    auto fileName = QFileDialog::getSaveFileName(d->mainWindow, tr("导出"), ".", "*.dat");
    if (fileName.isEmpty())
        return;
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    auto curve = d->configManage->specCalibrate("1")->stdCurve();
    if (curve.size() < 2000)
    {
        QMessageBox::warning(d->mainWindow, "", tr("\n无效标准曲线数据！\n"));
        return;
    }
    QTextStream s(&file);
    s << curve.size() << "\t1" << endl;
    for (auto v : curve)
        s << QString::number(v, 'f', 1) << endl;
    file.close();
    QMessageBox::information(d->mainWindow, "", tr("\n导出成功！\n"));
}

HE_GUI_END_NAMESPACE
