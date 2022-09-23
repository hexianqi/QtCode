#include "HMainWindowDemo_p.h"
#include "ui_HMainWindowDemo.h"
#include "HeCore/HAppContext.h"
#include "HeCore/HCore.h"
#include "HePlugin/HSingleAxisChart.h"
#include "HePlugin/HZoomChartView.h"
#include <QtCore/QTimer>
#include <QtCore/QTextStream>
#include <QtCharts/QValueAxis>
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QMessageBox>

QPolygonF toPolygon(vector<double> value)
{
    QPolygonF poly;
    for (uint i = 0; i < value.size(); i++)
        poly << QPointF(i, value.at(i));
    return poly;
}

HMainWindowDemo::HMainWindowDemo(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::HMainWindowDemo),
    d_ptr(new HMainWindowDemoPrivate)
{
    ui->setupUi(this);
    init();
}

HMainWindowDemo::~HMainWindowDemo()
{
    delete ui;
}

void HMainWindowDemo::showDeviceFailed(const QString &port, const QString &text)
{
    auto msg = tr("\n“%1”设备连接失败！错误原因“%2”。\n").arg(port, text);
    QMessageBox::critical(this, "", msg);
}

void HMainWindowDemo::showActionFailed(HActionType action, const QString &text)
{
    auto msg = tr("\n指令“%1”错误！错误原因是“%2”\n").arg(HCore::toComment(action), text);
    QMessageBox::warning(this, "", msg);
}

void HMainWindowDemo::handleAction(HActionType action)
{
    if (action == ACT_GET_SPECTRUM)
    {
        auto curve = d_ptr->testData->data("[采样值]").value<vector<double>>();
        auto rx = d_ptr->testData->data("[显色指数Rx]").value<vector<double>>();
        d_ptr->series1->replace(toPolygon(curve));
        d_ptr->specWidget->addPolygon(0, d_ptr->testData->data("[能量曲线]").value<QPolygonF>());

        QString text = "<body>";
        text += QString("<p> 峰值波长 = %1 nm </p>").arg(d_ptr->testData->toString("[峰值波长]"));
        text += QString("<p> 峰值带宽 = %1 nm </p>").arg(d_ptr->testData->toString("[峰值带宽]"));
        text += QString("<p>   主波长 = %1 nm </p>").arg(d_ptr->testData->toString("[主波长]"));
        text += QString("<p>   色纯度 = %1    </p>").arg(d_ptr->testData->toString("[色纯度]"));
        text += QString("<p>     色温 = %1 K  </p>").arg(d_ptr->testData->toString("[色温]"));
        text += QString("<p>  色坐标x = %1    </p>").arg(d_ptr->testData->toString("[色坐标x]"));
        text += QString("<p>  色坐标y = %1    </p>").arg(d_ptr->testData->toString("[色坐标y]"));
        text += QString("<p>  色坐标u = %1    </p>").arg(d_ptr->testData->toString("[色坐标u]"));
        text += QString("<p>  色坐标v = %1    </p>").arg(d_ptr->testData->toString("[色坐标v]"));
        text += QString("<p>      Duv = %1    </p>").arg(d_ptr->testData->toString("[Duv]"));
        text += QString("<p>   红色比 = %1 %  </p>").arg(d_ptr->testData->toString("[红色比]"));
        text += QString("<p>   蓝色比 = %1 %  </p>").arg(d_ptr->testData->toString("[蓝色比]"));
        text += QString("<p>   绿色比 = %1 %  </p>").arg(d_ptr->testData->toString("[绿色比]"));
        text += QString("<p>       Ra = %1    </p>").arg(d_ptr->testData->toString("[显色指数Ra]"));
        for (uint i = 0; i < rx.size(); i++)
            text += QString("<p>      R%1 = %2    </p>").arg(i+1, 2, 10, QChar('0')).arg(rx[i]);
        text += "</body>";
        ui->textBrowser->setText(text);
    }
    if (action == ACT_GET_SN)
    {
        QStringList list;
        auto sn = d_ptr->testData->data("[序列号]").value<vector<unsigned char>>();
        for (auto v : sn)
            list << QString("%1").arg(v, 3, 10, QChar('0'));
        ui->lineEdit->setText(list.join('-'));
    }
    if (action == ACT_GET_DATA)
    {
        auto poly = d_ptr->testData->data("[像元波长]").value<QPolygonF>();
        auto size = poly.size();
        ui->tableWidget->clearContents();
        ui->tableWidget->setRowCount(size);
        for (int i = 0; i < size; i++)
            ui->tableWidget->setRow(i, QStringList() << HCore::toString("[光谱像元]", poly[i].x()) << HCore::toString("[光谱波长]", poly[i].y()));
    }
}

void HMainWindowDemo::on_pushButton_01_clicked()
{
    d_ptr->testData->setData("[积分时间]", ui->doubleSpinBox->value());
    d_ptr->thread->addAction(ACT_SET_INTEGRAL_TIME);
}

void HMainWindowDemo::on_pushButton_02_clicked()
{
    d_ptr->thread->addAction(ACT_GET_SPECTRUM);
}

void HMainWindowDemo::on_pushButton_03_clicked()
{
    d_ptr->thread->addAction(ACT_GET_SN);
}

void HMainWindowDemo::on_pushButton_04_clicked()
{
    d_ptr->thread->addAction(ACT_GET_DATA);
}

void HMainWindowDemo::on_pushButton_11_clicked()
{
    d_ptr->stdCurve = d_ptr->testData->data("[采样值]").value<vector<double>>();
    if (d_ptr->stdCurve.empty())
        return;
    refreshStdCurve();
}

void HMainWindowDemo::on_pushButton_13_clicked()
{
    auto fileName = QFileDialog::getOpenFileName(this, tr("导入"), ".", "*.dat");
    if (fileName.isEmpty())
        return;
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    int i,n;
    double t;
    QString str;
    QTextStream s(&file);
    s >> n >> str;
    if (n < 2000)
    {
        QMessageBox::warning(this, "", tr("\n无效标准曲线数据！\n"));
        file.close();
        return;
    }
    d_ptr->stdCurve.clear();
    for (i = 0; i < n; i++)
    {
        s >> t;
        d_ptr->stdCurve.push_back(t);
    }
    file.close();
    refreshStdCurve();
    QMessageBox::information(this, "", tr("\n导入成功！\n"));
}

void HMainWindowDemo::on_pushButton_14_clicked()
{
    auto fileName = QFileDialog::getSaveFileName(this, tr("导出"), ".", "*.dat");
    if (fileName.isEmpty())
        return;
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    if (d_ptr->stdCurve.size() < 2000)
    {
        QMessageBox::warning(this, "", tr("\n无效标准曲线数据！\n"));
        return;
    }
    QTextStream s(&file);
    s << d_ptr->stdCurve.size() << "\t1" << endl;
    for (auto v : d_ptr->stdCurve)
        s << QString::number(v, 'f', 1) << endl;
    file.close();
    QMessageBox::information(this, "", tr("\n导出成功！\n"));
}

void HMainWindowDemo::init()
{
    d_ptr->testData = new HTestData();
    HAppContext::setContextPointer("ITestData", d_ptr->testData);

    auto sampleChartView = new HZoomChartView;
    auto axisX = new QValueAxis;
    axisX->setLabelFormat("%d");
    axisX->setRange(0, 2100);
    axisX->setTickCount(6);
    auto axisY = new QValueAxis;
    axisY->setLabelFormat("%d");
    axisY->setRange(0, 65535);
    axisY->setTickCount(6);
    auto chart = new HSingleAxisChart;
    chart->setAxisX(axisX);
    chart->setAxisY(axisY);
    d_ptr->series1 = new QLineSeries();
    d_ptr->series1->setName(tr("采样曲线"));
    chart->addSeries(d_ptr->series1);
    d_ptr->series2 = new QLineSeries();
    d_ptr->series2->setName(tr("标准曲线"));
    chart->addSeries(d_ptr->series2);
    sampleChartView->setChart(chart);
    ui->tabWidget->addTab(sampleChartView, tr("光谱采样曲线"));

    d_ptr->specWidget = new HSpecDiagramWidget;
    d_ptr->specWidget->setWaveRange(QPointF(380.0, 780.0));
    ui->tabWidget->addTab(d_ptr->specWidget, tr("相对光谱功率分布"));

    ui->tableWidget->setHorizontalHeaderLabels(QStringList() << tr("像元") << tr("波长"));
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->splitter->setStretchFactor(0, 5);
    ui->splitter->setStretchFactor(0, 1);

    d_ptr->thread = new HThreadDemo(this);
    connect(d_ptr->thread, &HThreadDemo::startFailed, this, &HMainWindowDemo::showDeviceFailed);
    connect(d_ptr->thread, &HThreadDemo::actionFailed, this, &HMainWindowDemo::showActionFailed);
    connect(d_ptr->thread, &HThreadDemo::actionFinished, this, &HMainWindowDemo::handleAction);
    QTimer::singleShot(1000, this, [=] { d_ptr->thread->start(); });
}

void HMainWindowDemo::refreshStdCurve()
{
    d_ptr->series2->replace(toPolygon(d_ptr->stdCurve));
    d_ptr->testData->setData("[标准数据]", QVariant::fromValue(d_ptr->stdCurve));
    d_ptr->thread->addAction(ACT_SET_DATA);
}
