#include "HGradeIsothermDialog_p.h"
#include "ui_HGradeIsothermDialog.h"
#include "HeAlgorithm/IChromaticity.h"
#include "HeAlgorithm/HSpecFacade.h"
#include "HeCore/HAppContext.h"
#include "HePlugin/HPluginHelper.h"
#include <QtCore/QSettings>
#include <QtCore/QDebug>

HE_ALGORITHM_USE_NAMESPACE
HE_CORE_USE_NAMESPACE
HE_GUI_BEGIN_NAMESPACE

HGradeIsothermDialog::HGradeIsothermDialog(QWidget *parent) :
    QDialog(parent),
    d_ptr(new HGradeIsothermDialogPrivate),
    ui(new Ui::HGradeIsothermDialog)
{
    ui->setupUi(this);
    init();
    readSettings();
    showData();
}

HGradeIsothermDialog::~HGradeIsothermDialog()
{
    qDebug() << __func__;
    writeSettings();
    delete ui;
}

QList<QPolygonF> HGradeIsothermDialog::levels()
{
    return d_ptr->levels;
}

void HGradeIsothermDialog::done(int result)
{
    if (result == QDialog::Accepted)
        saveData();
    QDialog::done(result);
}

void HGradeIsothermDialog::showData()
{
    ui->doubleSpinBox_01->setValue(d_ptr->tc.x());
    ui->doubleSpinBox_02->setValue(d_ptr->tc.y());
    ui->doubleSpinBox_03->setValue(d_ptr->duv.x());
    ui->doubleSpinBox_04->setValue(d_ptr->duv.y());
    ui->spinBox_01->setValue(d_ptr->count.x());
    ui->spinBox_02->setValue(d_ptr->count.y());
}

void HGradeIsothermDialog::saveData()
{
    auto tc1 = ui->doubleSpinBox_01->value();
    auto tc2 = ui->doubleSpinBox_02->value();
    auto duv1 = ui->doubleSpinBox_03->value();
    auto duv2 = ui->doubleSpinBox_04->value();
    auto count1 = ui->spinBox_01->value();
    auto count2 = ui->spinBox_02->value();
    if (count1 * count2 == 0)
        return;

    int i,j;
    QList<double> tcs;
    QList<double> duvs;
    QVector<QPolygonF> l;
    HSpecFacade facade;
    auto chromaticity = facade.chromaticity();


    for (i = 0; i <= count1; i++)
        tcs << tc1 + i * (tc2 - tc1) / count1;
    for (i = 0; i <= count2; i++)
        duvs << duv1 + i * (duv2 - duv1) / count2;

    for (i = 0; i <= count2; i++)
    {
        QPolygonF p;
        for (j = 0; j <= count1; j++)
            p << chromaticity->calcIsothermXY(tcs[j], duvs[i]).p2();
        l << p;
    }

    d_ptr->tc = QPointF(tc1, tc2);
    d_ptr->duv = QPointF(duv1, duv2);
    d_ptr->count = QPoint(count1, count2);
    d_ptr->levels.clear();
    for (i = 0; i < count1; i++)
        for (j = 0; j < count2; j++)
            d_ptr->levels.append(QPolygonF() << l[j][i] << l[j+1][i] << l[j+1][i+1] << l[j][i+1]);
}

void HGradeIsothermDialog::init()
{
    HPluginHelper::initWidget("[色温]", ui->doubleSpinBox_01);
    HPluginHelper::initWidget("[色温]", ui->doubleSpinBox_02);
    HPluginHelper::initWidget("[偏移量]", ui->doubleSpinBox_03);
    HPluginHelper::initWidget("[偏移量]", ui->doubleSpinBox_04);
    HPluginHelper::initWidget("[分级数]", ui->spinBox_01);
    HPluginHelper::initWidget("[分级数]", ui->spinBox_02);
}

void HGradeIsothermDialog::readSettings()
{
    auto fileName = HAppContext::getContextValue<QString>("Settings");
    auto settings = new QSettings(fileName, QSettings::IniFormat, this);
    settings->setIniCodec("utf-8");
    settings->beginGroup("GradeIsotherm");
    d_ptr->tc = settings->value("ColorTemperature", QPointF(2300, 6000)).toPointF();
    d_ptr->duv = settings->value("Duv", QPointF(-0.02, 0.02)).toPointF();
    d_ptr->count = settings->value("Count", QPoint(10, 2)).toPoint();
    settings->endGroup();
}

void HGradeIsothermDialog::writeSettings()
{
    auto fileName = HAppContext::getContextValue<QString>("Settings");
    auto settings = new QSettings(fileName, QSettings::IniFormat, this);
    settings->setIniCodec("utf-8");
    settings->beginGroup("GradeIsotherm");
    settings->setValue("ColorTemperature", d_ptr->tc);
    settings->setValue("Duv", d_ptr->duv);
    settings->setValue("Count", d_ptr->count);
    settings->endGroup();
}

HE_GUI_END_NAMESPACE
