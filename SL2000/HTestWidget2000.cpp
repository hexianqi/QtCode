#include "HTestWidget2000_p.h"
#include "HTestSetWidget2000.h"
#include "HDetailWidget2000.h"
#include "HeCore/HAppContext.h"
#include "HeData/IConfigManage.h"
#include "HeData/ITestData.h"
#include "HeData/IGradeCollection.h"
#include "HeData/ISpecCalibrate.h"
#include "HeController/IModel.h"
#include "HePlugin/HCie1931Widget.h"
#include "HeGui/HSpecEnergyWidget.h"
#include "HeGui/HSpecChromatismChartView.h"
#include "HeGui/HResultTableWidget.h"
#include <QtCore/QDateTime>
#include <QtCore/QSettings>
#include <QtWidgets/QAction>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QMenu>
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QMessageBox>
#include <QtCore/QDebug>

HTestWidget2000Private::HTestWidget2000Private()
{
    testData->setData("[使用调整]", false);
    displays = QStringList() << "[测量日期]" << "[测量时间]"
                             << "[分级]"
                             << "[色容差]"
                             << "[光谱光通量]" << "[光功率]"
                             << "[主波长]" << "[峰值波长]" << "[峰值带宽]"
                             << "[色温]" << "[色纯度]"
                             << "[色坐标]" << ("[色坐标uvp]") << "[Duv]"
                             << "[红色比]" << "[绿色比]" << "[蓝色比]"
                             << "[显色指数]" <<"[显色指数Rx]";

    configManage = HAppContext::getContextPointer<IConfigManage>("IConfigManage");
    energyWidget = new HSpecEnergyWidget;
    chromatismWidget = new HSpecChromatismChartView;
    cieWidget = new HCie1931Widget;
    resultWidget = new HResultTableWidget;
    testSetWidget = new HTestSetWidget2000;
    detailWidget = new HDetailWidget2000;
}

HTestWidget2000::HTestWidget2000(QWidget *parent) :
    HTestWidget2(*new HTestWidget2000Private, parent)
{
    readSettings();
    init();
    resetGrade();
}

HTestWidget2000::HTestWidget2000(HTestWidget2000Private &p, QWidget *parent) :
    HTestWidget2(p, parent)
{
}

HTestWidget2000::~HTestWidget2000()
{
    qDebug() << __func__;
    writeSettings();
}

void HTestWidget2000::initialize(QVariantMap /*param*/)
{

}

QString HTestWidget2000::typeName()
{
    return "HTestWidget2000";
}

bool HTestWidget2000::setTest(bool b)
{
    Q_D(HTestWidget2000);
    return d->testSetWidget->setTestState(b);
}

void HTestWidget2000::handleAction(HActionType action)
{
    Q_D(HTestWidget2000);
    if (action >= 0xF0000000)
    {
        setTest(false);
        clearResult();
        if (action == ACT_RESET_SPECTRUM)
            d->energyWidget->initCoordinate();
        if (action == ACT_RESET_CHROMATISM)
            d->chromatismWidget->initMenuShow();
        if (action == ACT_RESET_GRADE)
            resetGrade();
        return;
    }
    if (action == ACT_GET_SPECTRUM)
    {
        postProcess();
        refreshWidget();
    }
    d->testSetWidget->handleAction(action);
}

void HTestWidget2000::clearResult()
{
    Q_D(HTestWidget2000);
    d->cieWidget->clearPoint();
    d->resultWidget->clearResult();
}

bool HTestWidget2000::canExport()
{
    // 判断是否可导出
    return true;
}

void HTestWidget2000::createAction()
{
    Q_D(HTestWidget2000);
    HTestWidget2::createAction();
    d->actionAdjust = new QAction(tr("使用调整(&A)"), this);
    d->actionAdjust->setCheckable(true);
    d->actionAdjust->setChecked(d->testData->data("[使用调整]").toBool());
    d->actionSetRam = new QAction(tr("写入数据到设备(&S)"), this);
    d->actionGetRam = new QAction(tr("从设备读取数据(&G)"), this);
    d->actionImportCurve = new QAction(tr("导入标准曲线(&I)"), this);
    d->actionExportCurve = new QAction(tr("导出标准曲线(&E)"), this);
    connect(d->actionAdjust, &QAction::triggered, this, [=](bool b){ d->testData->setData("[使用调整]", b); });
    connect(d->actionSetRam, &QAction::triggered, this, [=]{ d->model->addAction(ACT_SET_RAM); });
    connect(d->actionGetRam, &QAction::triggered, this, [=]{ d->model->addAction(ACT_GET_RAM); });
    connect(d->actionImportCurve, &QAction::triggered, this, &HTestWidget2000::importCurve);
    connect(d->actionExportCurve, &QAction::triggered, this, &HTestWidget2000::exportCurve);
}

void HTestWidget2000::createWidget()
{
    Q_D(HTestWidget2000);
    auto layout = new QGridLayout(this);
    auto tabWidget1 = new QTabWidget;
    auto tabWidget2 = new QTabWidget;
    auto tabWidget3 = new QTabWidget;
    auto splitter1 = new QSplitter(Qt::Horizontal);
    auto splitter2 = new QSplitter(Qt::Vertical);
    d->resultWidget->setDisplay(d->displays);
    d->resultWidget->setSelected(d->tableSelecteds);
    d->resultWidget->addAction(d->actionClear);
    tabWidget1->setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding));
    tabWidget1->addTab(d->energyWidget, d->energyWidget->windowTitle());
    tabWidget2->addTab(d->cieWidget, d->cieWidget->windowTitle());
    tabWidget2->addTab(d->chromatismWidget, d->chromatismWidget->windowTitle());
    tabWidget3->addTab(d->detailWidget, tr("当次结果"));
    tabWidget3->addTab(d->resultWidget, tr("结果列表"));
    splitter1->addWidget(tabWidget1);
    splitter1->addWidget(tabWidget2);
    splitter1->setHandleWidth(15);
    splitter1->setStretchFactor(0, 2);
    splitter1->setStretchFactor(1, 1);
    splitter2->addWidget(splitter1);
    splitter2->addWidget(tabWidget3);
    splitter2->setHandleWidth(15);
    splitter2->setStretchFactor(1, 1);
    layout->addWidget(splitter2);
    connect(d->testSetWidget, &ITestSetWidget::testStateChanged, this, &HTestWidget2000::handleTestStateChanged);
}

void HTestWidget2000::createMenu()
{
    Q_D(HTestWidget2000);
    auto menu1 = new QMenu(tr("测试配置(&T)"));
    auto menu2 = new QMenu(tr("设备配置(&T)"));
    menu1->addAction(d->actionAdjust);
    menu2->addAction(d->actionSetRam);
    menu2->addAction(d->actionGetRam);
    menu2->addAction(d->actionImportCurve);
    menu2->addAction(d->actionExportCurve);
    d->menus << menu1 << menu2;
}

void HTestWidget2000::createToolBar()
{
    Q_D(HTestWidget2000);
    auto toolBar1 = new QToolBar(tr("设置(&S)"));
    auto toolBar2 = new QToolBar(tr("操作(&O)"));
    toolBar1->addWidget(d->testSetWidget);
    toolBar2->addAction(d->actionStart);
    toolBar2->addAction(d->actionStop);
    toolBar2->addAction(d->actionClear);
    toolBar2->addAction(d->actionExportExcel);
    toolBar2->addAction(d->actionExportDatabase);
    toolBar2->addAction(d->actionPrintPreview);
    d->toolBars << toolBar1 << toolBar2;
}

void HTestWidget2000::handleTestStateChanged(bool b)
{
    Q_D(HTestWidget2000);
    d->actionStart->setEnabled(!b);
    d->actionStop->setEnabled(b);
    d->actionClear->setEnabled(!b);
    d->actionExportExcel->setEnabled(!b);
    d->actionExportDatabase->setEnabled(!b);
    d->actionPrintPreview->setEnabled(!b);
}

void HTestWidget2000::resetGrade()
{
    Q_D(HTestWidget2000);
    auto v = d->configManage->gradeCollection()->levels("[色坐标]");
    auto p = v.value<QList<QPolygonF>>();
    d->cieWidget->setGrade(p);
}

void HTestWidget2000::refreshWidget()
{
    Q_D(HTestWidget2000);
    d->energyWidget->refreshWidget();
    d->detailWidget->refreshWidget();
    d->chromatismWidget->refreshWidget();
    d->cieWidget->addPoint(d->testData->data("[色坐标]").toPointF());
    d->resultWidget->refreshResult(0, d->testSetWidget->testMode() == 0);
}

void HTestWidget2000::postProcess()
{
    Q_D(HTestWidget2000);
    d->configManage->postProcess(d->testData, d->displays);
    d->testData->setData("[测量日期时间]", QDateTime::currentDateTime());
}

void HTestWidget2000::importCurve()
{
    Q_D(HTestWidget2000);
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

void HTestWidget2000::exportCurve()
{
    Q_D(HTestWidget2000);
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

void HTestWidget2000::readSettings()
{
    Q_D(HTestWidget2000);
    auto fileName = HAppContext::getContextValue<QString>("Settings");
    auto settings = new QSettings(fileName, QSettings::IniFormat, this);
    settings->beginGroup("TestWidget");
    d->tableSelecteds = settings->value("sTableSelected", d->displays).toStringList();
    d->testData->setData("[使用调整]", settings->value("bAdjust", false));
    d->testData->setData("[CCD类型]", settings->value("sCCD", "1305"));
    d->testData->setData("[CCD偏差]", settings->value("fOffset", 55.0));
    settings->endGroup();
}

void HTestWidget2000::writeSettings()
{
    Q_D(HTestWidget2000);
    auto fileName = HAppContext::getContextValue<QString>("Settings");
    auto settings = new QSettings(fileName, QSettings::IniFormat, this);
    settings->beginGroup("TestWidget");
    settings->setValue("sTableSelected", d->resultWidget->selected());
    settings->setValue("bAdjust", d->testData->data("[使用调整]"));
    settings->setValue("sCCD", d->testData->data("[CCD类型]"));
    settings->setValue("fOffset", d->testData->data("[CCD偏差]"));
    settings->endGroup();
}
