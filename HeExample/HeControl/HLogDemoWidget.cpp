#include "HLogDemoWidget_p.h"
#include "ui_HLogDemoWidget.h"
#include "HLogNetworkService.h"
#include "HeCore/HKeepLogFile.h"
#include "HeCore/HLogRedirectService.h"
#include <QtCore/QTimer>
#include <QtCore/QDateTime>

HE_BEGIN_NAMESPACE

HLogDemoWidget::HLogDemoWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HLogDemoWidget),
    d_ptr(new HLogDemoWidgetPrivate)
{
    ui->setupUi(this);
    init();
}

HLogDemoWidget::~HLogDemoWidget()
{
    delete ui;
}

void HLogDemoWidget::on_pushButton_clicked()
{
    append("手动插入消息");
}

void HLogDemoWidget::on_checkBox_1_clicked(bool b)
{
    if (b)
        d_ptr->logRedirectService->start();
    else
        d_ptr->logRedirectService->stop();
}

void HLogDemoWidget::on_checkBox_2_clicked(bool b)
{
    if (b)
    {
        d_ptr->logNetworkService->setListenPort(ui->spinBox->value());
        d_ptr->logNetworkService->start();
    }
    else
        d_ptr->logRedirectService->stop();
}

void HLogDemoWidget::on_checkBox_3_clicked(bool b)
{
    if (b)
        d_ptr->timer->start();
    else
        d_ptr->timer->stop();
}

void HLogDemoWidget::on_comboBox_2_currentIndexChanged(int index)
{
    auto value = ui->comboBox_2->itemData(index).toInt();
    d_ptr->logFile->setMaxSize(value);
}

void HLogDemoWidget::on_comboBox_3_currentIndexChanged(int index)
{
    auto value = ui->comboBox_3->itemData(index).toInt();
    d_ptr->logFile->setMaxRow(value);
}

void HLogDemoWidget::on_listWidget_itemPressed(QListWidgetItem *item)
{
    quint32 types = 0;
    item->setCheckState(item->checkState() == Qt::Checked ? Qt::Unchecked : Qt::Checked);

    for (int i = 0; i < ui->listWidget->count(); ++i)
    {
        auto item = ui->listWidget->item(i);
        if (item->checkState() == Qt::Checked)
            types += item->data(Qt::UserRole).toInt();
    }
    d_ptr->logRedirectService->setMsgType(HLogRedirectService::MsgType(types));
}

void HLogDemoWidget::append(QString text)
{
    if (d_ptr->count >= 100)
    {
        d_ptr->count = 0;
        ui->textEdit->clear();
    }

    auto type = ui->comboBox_1->currentIndex();
    auto str1 = ui->checkBox_1->isChecked() ? "" : ui->comboBox_1->currentText();
    auto str2 = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");
    auto str3 = text.isEmpty() ? "自动插入消息" : text;
    auto msg = QString("%1 当前时间: %2 %3").arg(str1, str2, str3);

    d_ptr->count++;
    ui->textEdit->append(msg);

    // 根据不同的类型打印
    // 转换要分两部走不然msvc的debug版本会乱码(英文也一样)
    // auto data = msg.toUtf8().data();
    auto buffer = msg.toUtf8();
    auto data = buffer.constData();
    if (type == 0)
        qDebug("%s", data);
    else if (type == 1)
        qInfo("%s", data);
    else if (type == 2)
        qWarning("%s", data);
    else if (type == 3)
        qCritical("%s", data);
    else if (type == 4) // 调用下面这个打印完会直接退出程序
        qFatal("%s", data);
}

void HLogDemoWidget::init()
{
    d_ptr->logRedirectService = HLogRedirectService::instance();
    d_ptr->logRedirectService->setUseContext(false);
    d_ptr->logNetworkService = HLogNetworkService::instance();
    d_ptr->logFile = new HKeepLogFile(this);
    d_ptr->timer = new QTimer(this);
    d_ptr->timer->setInterval(100);
    auto types = QStringList() << "Debug" << "Info" << "Warning" << "Critical" << "Fatal";
    auto datas = QStringList() << "1" << "2" << "4" << "8" << "16";
    ui->comboBox_1->addItems(types);
    ui->comboBox_2->addItem("不启用",  0);
    ui->comboBox_2->addItem(" 5KB",    5);
    ui->comboBox_2->addItem("10KB",    10);
    ui->comboBox_2->addItem("30KB",    30);
    ui->comboBox_2->addItem(" 1MB",    1024);
    ui->comboBox_3->addItem("不启用",  0);
    ui->comboBox_3->addItem("100条",   100);
    ui->comboBox_3->addItem("500条",   500);
    ui->comboBox_3->addItem("2000条",  2000);
    ui->comboBox_3->addItem("10000条", 10000);

    for (int i = 0; i < types.count(); ++i)
    {
        auto item = new QListWidgetItem;
        item->setText(types.at(i));
        item->setData(Qt::UserRole, datas.at(i));
        item->setCheckState(Qt::Checked);
        ui->listWidget->addItem(item);
    }
    // 必须用信号槽形式,不然提示 QSocketNotifier: Socket notifiers cannot be enabled or disabled from another thread
    // 估计日志钩子可能单独开了线程
    connect(d_ptr->logRedirectService, SIGNAL(output(QString)), d_ptr->logNetworkService, SLOT(sendData(QString)));
    connect(d_ptr->logRedirectService, SIGNAL(output(QString)), d_ptr->logFile, SLOT(append(QString)));
    connect(d_ptr->timer, SIGNAL(timeout()), this, SLOT(append()));
}

HE_END_NAMESPACE
