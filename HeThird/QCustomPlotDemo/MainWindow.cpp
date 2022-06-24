#include "MainWindow.h"
#include "ui_MainWindow.h"

HMainWindow::HMainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

HMainWindow::~HMainWindow()
{
    delete ui;
}

