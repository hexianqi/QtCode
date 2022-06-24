#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QtGui/QPainter>
#include <QProgressDialog>
#include <QTimer>
#include <QFile>
#include <QDir>
#include <QDebug>

HMainWindow::HMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    _timer = new QTimer(this);
    _progressDialog = new QProgressDialog(tr("正在采样...."), tr("取消"), 0, 100, this);
    _progressDialog->reset();
    connect(_timer, &QTimer::timeout, this, &HMainWindow::test);
    connect(_progressDialog, &QProgressDialog::canceled, _timer, &QTimer::stop);


    ui->comboBox->addItem("111");
    ui->comboBox->addItem("222");
    ui->comboBox->addItem("333");
    ui->comboBox->addItem("444");
    connect(ui->comboBox, SIGNAL(activated(int)), this, SLOT(CheckActiveSignal(int)));
    connect(ui->comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(CheckIndexChangedSignal(int)));
}

HMainWindow::~HMainWindow()
{
    delete ui;
}

void HMainWindow::on_pushButton_clicked()
{
    _testValue = 0;
    _testVector.resize(100);
    qDebug() << "Start: 0 - " << _testVector.size();
    _progressDialog->setRange(0, _testVector.size());
    _progressDialog->setValue(_testValue);
    _timer->start(100);
}

//void MainWindow::paintEvent(QPaintEvent *)
//{
//    QPainter painter(this);
//    painter.setWindow(0, 0, 200, 200);
//    painter.fillRect(0, 0, 200, 200, Qt::yellow);
//    painter.setViewport(0, 0, 100, 100);
//    painter.fillRect(0, 0, 100, 100, Qt::red);
//}

void HMainWindow::test()
{
    qDebug() << _testValue;
    qDebug() << _testValue++;
    qDebug() << _testValue;
    qDebug() << "EEE";


//    _testVector[_testValue++] = _progressDialog->value();

    _progressDialog->setValue(_testValue);
    if (_testValue >= _testVector.size())
        _timer->stop();
}

void HMainWindow::CheckActiveSignal(int value)
{
    qDebug() << "CheckActiveSignal " << value;
}

void HMainWindow::CheckIndexChangedSignal(int value)
{
    qDebug() << "CheckIndexChangedSignal " << value;
}

void HMainWindow::on_comboBox_currentIndexChanged(int value)
{
    qDebug() << "on_comboBox_currentIndexChanged " << value;
}
