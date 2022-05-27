#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QtGui/QPainter>
#include <QProgressDialog>
#include <QTimer>
#include <QFile>
#include <QDir>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    _timer = new QTimer(this);
    _progressDialog = new QProgressDialog(tr("正在采样...."), tr("取消"), 0, 100, this);
    _progressDialog->reset();
    connect(_timer, &QTimer::timeout, this, &MainWindow::test);
    connect(_progressDialog, &QProgressDialog::canceled, _timer, &QTimer::stop);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
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

void MainWindow::test()
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
