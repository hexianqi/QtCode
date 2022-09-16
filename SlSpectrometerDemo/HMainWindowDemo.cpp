#include "HMainWindowDemo.h"
#include "./ui_HMainWindowDemo.h"

HMainWindowDemo::HMainWindowDemo(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::HMainWindowDemo)
{
    ui->setupUi(this);
}

HMainWindowDemo::~HMainWindowDemo()
{
    delete ui;
}

