#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QPainter>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setWindow(0, 0, 200, 200);
    painter.fillRect(0, 0, 200, 200, Qt::yellow);
    painter.setViewport(0, 0, 100, 100);
    painter.fillRect(0, 0, 100, 100, Qt::red);
}
