#include "HFlatStyleWidget.h"
#include "ui_HFlatStyleWidget.h"
#include "HFlatStyle.h"

HE_CONTROL_BEGIN_NAMESPACE

HFlatStyleWidget::HFlatStyleWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HFlatStyleWidget)
{
    ui->setupUi(this);
    init();
}

HFlatStyleWidget::~HFlatStyleWidget()
{
    delete ui;
}

void HFlatStyleWidget::init()
{
    auto style = new HFlatStyle(this);
    style->setStyle(ui->pushButton_1, 8, 5, "#FFFFFF", "#34495E", "#F0F0F0", "#4E6D8C", "#B8C6D1", "#2D3E50");
    style->setStyle(ui->pushButton_2, 8, 5, "#E6F8F5", "#1ABC9C", "#FFFFFF", "#2EE1C1", "#A7EEE6", "#16A086");
    style->setStyle(ui->pushButton_3, 8, 5, "#FFFFFF", "#3498DB", "#E5FEFF", "#5DACE4", "#A0DAFB", "#2483C7");
    style->setStyle(ui->pushButton_4, 8, 5, "#FFFFFF", "#E74C3C", "#FFF5E7", "#EC7064", "#F5A996", "#DC2D1A");
    style->setStyle(ui->lineEdit_1, 8, 3, 2, "#DCE4EC", "#34495E");
    style->setStyle(ui->lineEdit_2, 8, 5, 2, "#DCE4EC", "#1ABC9C");
    style->setStyle(ui->lineEdit_3, 8, 3, 1, "#DCE4EC", "#3498DB");
    style->setStyle(ui->lineEdit_4, 8, 3, 1, "#DCE4EC", "#E74C3C");
    style->setStyle(ui->progressBar_1, 9, 8, 5, "#E8EDF2", "#E74C3C");
    style->setStyle(ui->progressBar_2, 9, 8, 5, "#E8EDF2", "#1ABC9C");
    style->setStyle(ui->horizontalSlider_1, 8, "#E8EDF2", "#1ABC9C", "#1ABC9C");
    style->setStyle(ui->horizontalSlider_2, 10, "#E8EDF2", "#E74C3C", "#E74C3C");
    style->setStyle(ui->verticalSlider_1, 10, "#E8EDF2", "#34495E", "#34495E");
    style->setStyle(ui->radioButton_1, 8, "#D7DBDE", "#34495E");
    style->setStyle(ui->radioButton_2, 8, "#D7DBDE", "#1ABC9C");
    style->setStyle(ui->radioButton_3, 8, "#D7DBDE", "#3498DB");
    style->setStyle(ui->radioButton_4, 8, "#D7DBDE", "#E74C3C");
    style->setStyle(ui->checkBox_1, 2, "#D7DBDE", "#34495E");
    style->setStyle(ui->checkBox_2, 2, "#D7DBDE", "#1ABC9C");
    style->setStyle(ui->checkBox_3, 2, "#D7DBDE", "#3498DB");
    style->setStyle(ui->checkBox_4, 2, "#D7DBDE", "#E74C3C");
    style->setStyle(ui->horizontalScrollBar_1, 6, 120, 12, "#606060", "#34495E", "#1ABC9C", "#E74C3C");
    style->setStyle(ui->verticalScrollBar_1, 8, 120, 20, "#E8EDF2", "#1ABC9C", "#1ABC9C", "#E74C3C");
}

HE_CONTROL_END_NAMESPACE
