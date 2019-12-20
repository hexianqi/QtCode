#include "HPngAmend_p.h"
#include "ui_HPngAmend.h"
#include <QtConcurrent/QtConcurrentMap>
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QMessageBox>

HE_CONTROL_BEGIN_NAMESPACE

HPngAmend::HPngAmend(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HPngAmend),
    d_ptr(new HPngAmendPrivate)
{
    ui->setupUi(this);
    init();
}

HPngAmend::~HPngAmend()
{
    delete ui;
}

void HPngAmend::on_pushButton_1_clicked()
{
    auto file = QFileDialog::getOpenFileName(this, "选择PNG文件", ".", "PNG图片文件(*.png)");
    if (file.isEmpty())
        return;
    ui->lineEdit_1->setText(file);
    ui->progressBar->setValue(0);
}

void HPngAmend::on_pushButton_2_clicked()
{
    auto dir = QFileDialog::getExistingDirectory(this, "选择目录");
    if (dir.isEmpty())
        return;
    ui->lineEdit_2->setText(dir);
    ui->progressBar->setValue(0);
}

void HPngAmend::on_pushButton_3_clicked()
{
    if (d_ptr->watcher->isRunning())
    {
        d_ptr->watcher->cancel();
        d_ptr->watcher->waitForFinished();
    }

    QStringList files;
    auto currentFile = ui->lineEdit_1->text().trimmed();
    if (!currentFile.isEmpty())
        files << currentFile;

    auto currentDir = ui->lineEdit_2->text().trimmed();
    if (!currentDir.isEmpty())
    {
        QDir imagePath(currentDir);
        auto list = imagePath.entryList(QStringList() << "*.png");
        for(auto name : list)
            files << currentDir + QDir::separator() + name;
    }

    auto amend = [=](const QString &file) {
        QImage image(file);
        image.save(file, "png");
    };
    d_ptr->watcher->setFuture(QtConcurrent::map(files, amend));
}

void HPngAmend::init()
{
    d_ptr->watcher = new QFutureWatcher<void>(this);
    connect(d_ptr->watcher, &QFutureWatcher<void>::progressRangeChanged, ui->progressBar, &QProgressBar::setRange);
    connect(d_ptr->watcher, &QFutureWatcher<void>::progressValueChanged, ui->progressBar, &QProgressBar::setValue);
    connect(d_ptr->watcher, &QFutureWatcher<void>::finished, this, [=] { QMessageBox::information(this, tr("提示"), tr("修改完成！")); });
    ui->progressBar->setRange(0, 0);
    ui->progressBar->setValue(0);
    setWindowTitle("PNG警告去除工具");
}

HE_CONTROL_END_NAMESPACE
