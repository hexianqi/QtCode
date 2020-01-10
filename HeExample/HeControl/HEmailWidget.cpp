#include "HEmailWidget_p.h"
#include "ui_HEmailWidget.h"
#include "HRegularExpressionHelper.h"
#include "HSendEmailThread.h"
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QFileIconProvider>
#include <QtWidgets/QMessageBox>

HE_CONTROL_BEGIN_NAMESPACE

HEmailWidget::HEmailWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HEmailWidget),
    d_ptr(new HEmailWidgetPrivate)
{
    ui->setupUi(this);
    init();
}

HEmailWidget::~HEmailWidget()
{
    d_ptr->thread->stop();
    delete ui;
}

void HEmailWidget::on_pushButton_1_clicked()
{
    if (!check())
        return;

    QStringList list;
    for (int i = 0; i < ui->listWidget->count(); i++)
        list << ui->listWidget->item(i)->text();
    d_ptr->thread->setSender(ui->lineEdit_001->text());
    d_ptr->thread->setSenderPwd(ui->lineEdit_002->text());
    d_ptr->thread->setRecipientTo(ui->lineEdit_003->text());
    d_ptr->thread->setRecipientCc(ui->lineEdit_004->text());
    d_ptr->thread->setRecipientBcc(ui->lineEdit_005->text());
    d_ptr->thread->send(ui->lineEdit_006->text(), ui->textBrowser->toHtml(), list.join(';'));
}

void HEmailWidget::on_pushButton_2_clicked()
{
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::ExistingFiles);
    if (dialog.exec())
    {
        QFileIconProvider provider;
        for (auto file : dialog.selectedFiles())
        {
            QFileInfo info(file);
            ui->listWidget->addItem(new QListWidgetItem(provider.icon(info), info.fileName()));
        }
        ui->listWidget->setVisible(ui->listWidget->count() > 0);
    }
}

void HEmailWidget::on_pushButton_3_clicked()
{
    if (ui->listWidget->count() == 0)
        return;
    ui->listWidget->clear();
    ui->listWidget->setVisible(false);
}

void HEmailWidget::init()
{
    ui->lineEdit_001->setValidator(HRegularExpressionHelper::email(this));
    ui->listWidget->setVisible(false);
    d_ptr->thread = new HSendEmailThread(this);
    connect(d_ptr->thread, &HSendEmailThread::receiveEmailResult, this, [=](QString value) { QMessageBox::information(this, tr("提示"), value); });
    d_ptr->thread->start();
    setWindowTitle(tr("邮件发送工具"));
}

bool HEmailWidget::check()
{
    if (ui->lineEdit_001->text().isEmpty())
    {
        QMessageBox::critical(this, tr("错误"), tr("用户不能为空!"));
        ui->lineEdit_001->setFocus();
        return false;
    }
    if (ui->lineEdit_002->text().isEmpty())
    {
        QMessageBox::critical(this, tr("错误"), tr("用户密码不能为空!"));
        ui->lineEdit_002->setFocus();
        return false;
    }
    if (ui->lineEdit_003->text().isEmpty())
    {
        QMessageBox::critical(this, tr("错误"), tr("收件人不能为空!"));
        ui->lineEdit_003->setFocus();
        return false;
    }
    if (ui->lineEdit_006->text().isEmpty())
    {
        QMessageBox::critical(this, tr("错误"), tr("邮件标题不能为空!"));
        ui->lineEdit_006->setFocus();
        return false;
    }
    return true;
}

HE_CONTROL_END_NAMESPACE
