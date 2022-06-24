#include "HBase64ConvertWidget.h"
#include "ui_HBase64ConvertWidget.h"
#include "HBase64Helper.h"
#include <QtCore/QElapsedTimer>
#include <QtWidgets/QFileDialog>

HE_BEGIN_NAMESPACE

HBase64ConvertWidget::HBase64ConvertWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HBase64ConvertWidget)
{
    ui->setupUi(this);
    setWindowTitle(tr("Base64编解码"));
}

HBase64ConvertWidget::~HBase64ConvertWidget()
{
    delete ui;
}

void HBase64ConvertWidget::on_pushButton_1_clicked()
{
    auto fileName = ui->lineEdit_1->text().trimmed();
    if (fileName.isEmpty())
        return;

    QElapsedTimer time;
    time.start();
    ui->textEdit_2->setText(HBase64Helper::toBase64(QImage(fileName)));
    ui->label_2->setText(QString("图片转Base64 用时 %1 毫秒").arg(time.nsecsElapsed() / 1000000.0, 0, 'f', 3));
    ui->tabWidget->setCurrentIndex(2);
}

void HBase64ConvertWidget::on_pushButton_2_clicked()
{
    QString text = ui->textEdit_2->toPlainText().trimmed();
    if (text.isEmpty())
        return;

    QElapsedTimer time;
    time.start();
    auto pixmap = QPixmap::fromImage(HBase64Helper::toImage(text));
    pixmap = pixmap.scaled(ui->label_1->size() - QSize(4, 4), Qt::KeepAspectRatio);
    ui->label_1->setPixmap(pixmap);
    ui->label_2->setText(QString("Base64转图片 用时 %1 毫秒").arg(time.nsecsElapsed() / 1000000.0, 0, 'f', 3));
    ui->tabWidget->setCurrentIndex(0);
}

void HBase64ConvertWidget::on_pushButton_3_clicked()
{
    auto text = ui->textEdit_1->toPlainText().trimmed();
    if (text.isEmpty())
        return;

    QElapsedTimer time;
    time.start();
    ui->textEdit_2->setText(HBase64Helper::toBase64(text));
    ui->label_2->setText(QString("文字转Base64 用时 %1 毫秒").arg(time.nsecsElapsed() / 1000000.0, 0, 'f', 3));
    ui->tabWidget->setCurrentIndex(2);
}

void HBase64ConvertWidget::on_pushButton_4_clicked()
{
    QString text = ui->textEdit_2->toPlainText().trimmed();
    if (text.isEmpty())
        return;

    QElapsedTimer time;
    time.start();
    ui->textEdit_1->setText(HBase64Helper::toText(text));
    ui->label_2->setText(QString("Base64转文字 用时 %1 毫秒").arg(time.nsecsElapsed() / 1000000.0, 0, 'f', 3));
    ui->tabWidget->setCurrentIndex(1);
}

void HBase64ConvertWidget::on_pushButton_5_clicked()
{
    ui->label_1->clear();
    ui->label_2->clear();
    ui->textEdit_1->clear();
    ui->textEdit_2->clear();
}

void HBase64ConvertWidget::on_pushButton_6_clicked()
{
    auto fileName = QFileDialog::getOpenFileName(this, "选择文件", "", "图片(*.png *.bmp *.jpg)");
    if (fileName.isEmpty())
        return;
    ui->lineEdit_1->setText(fileName);
    QPixmap pixmap(fileName);
    pixmap = pixmap.scaled(ui->label_1->size() - QSize(4, 4), Qt::KeepAspectRatio);
    ui->label_1->setPixmap(pixmap);
}

HE_END_NAMESPACE
