#include "HImportCurveHandler_p.h"
#include "IMainWindow.h"
#include "HeData/IConfigManage.h"
#include "HeData/ISpecCalibrate.h"
#include "HeController/IModel.h"
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QMessageBox>
#include <QtCore/QDebug>

HE_GUI_BEGIN_NAMESPACE

HImportCurveHandler::HImportCurveHandler(QObject *parent) :
    HAbstractConfigHandler(*new HImportCurveHandlerPrivate, parent)
{
}

HImportCurveHandler::~HImportCurveHandler()
{
    qDebug() << __func__;
}

void HImportCurveHandler::initialize(QVariantMap /*param*/)
{

}

QString HImportCurveHandler::typeName()
{
    return "HSpecCalibrateHandler";
}

void HImportCurveHandler::execute(QObject */*sender*/, QVariantMap /*param*/)
{
    Q_D(HImportCurveHandler);
    auto fileName = QFileDialog::getOpenFileName(d->mainWindow, tr("导入"), ".", "*.dat");
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
        QMessageBox::warning(d->mainWindow, "", tr("\n无效标准曲线数据！\n"));
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
    d->model->addAction(ACT_RESET_SPECTRUM);
    QMessageBox::information(d->mainWindow, "", tr("\n导入成功！\n"));
}

HE_GUI_END_NAMESPACE
