#include "HGifWidget_p.h"
#include "ui_HGifWidget.h"
#include "HMoveEventFilter.h"
#include <QtCore/QDateTime>
#include <QtCore/QTimer>
#include <QtGui/QMouseEvent>
#include <QtGui/QPainter>
#include <QtGui/QScreen>
#include <QtGui/QDesktopServices>
#include <QtWidgets/QStyle>
#include <QtWidgets/QFileDialog>

HE_BEGIN_NAMESPACE

HGifWidget::HGifWidget(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HGifWidget),
    d_ptr(new HGifWidgetPrivate)
{
    ui->setupUi(this);
    init();
}

HGifWidget::~HGifWidget()
{
    if (d_ptr->timer->isActive())
        d_ptr->timer->stop();
    delete ui;
}

void HGifWidget::setBorderWidth(int value)
{
    if (d_ptr->borderWidth == value)
        return;
    d_ptr->borderWidth = value;
    update();
}

void HGifWidget::setBackground(const QColor &value)
{
    if (d_ptr->background == value)
        return;
    d_ptr->background = value;
    update();
}

int HGifWidget::borderWidth() const
{
    return d_ptr->borderWidth;
}

QColor HGifWidget::background() const
{
    return d_ptr->background;
}

void HGifWidget::resizeEvent(QResizeEvent *e)
{
    if (d_ptr->isStart)
        return;
    ui->spinBox_32->setValue(ui->widget_2->width());
    ui->spinBox_33->setValue(ui->widget_2->height());
    QDialog::resizeEvent(e);
}

void HGifWidget::paintEvent(QPaintEvent *)
{
    int width = ui->spinBox_32->value();
    int height = ui->spinBox_33->value();
    d_ptr->screen = QRect(d_ptr->borderWidth, ui->widget_1->height(), width - (d_ptr->borderWidth * 2), height);

    QPainter painter(this);
    painter.setPen(Qt::NoPen);
    painter.setBrush(d_ptr->background);
    painter.drawRoundedRect(rect(), 5, 5);
    painter.setCompositionMode(QPainter::CompositionMode_Clear);
    painter.fillRect(d_ptr->screen, Qt::SolidPattern);
}

void HGifWidget::saveImage()
{
    if (d_ptr->gifWriter == nullptr)
        return;

    auto pixmap = QApplication::primaryScreen()->grabWindow(0, x() + d_ptr->screen.x(), y() + d_ptr->screen.y(), d_ptr->screen.width(), d_ptr->screen.height());
    auto image = pixmap.toImage().convertToFormat(QImage::Format_RGBA8888);
    d_ptr->gif->GifWriteFrame(d_ptr->gifWriter, image.bits(), d_ptr->screen.width(), d_ptr->screen.height(), d_ptr->fps);
}

void HGifWidget::closeAll()
{
    clearWriter();
    delete d_ptr->gif;
    d_ptr->gif = nullptr;
    close();
}

void HGifWidget::record()
{
    if (d_ptr->isStart)
    {
        d_ptr->timer->stop();
        d_ptr->gif->GifEnd(d_ptr->gifWriter);
        clearWriter();
        ui->label_34->setText(tr("录制完成：%1").arg(d_ptr->fileName));
        QDesktopServices::openUrl(d_ptr->fileName);
    }
    else
    {
        d_ptr->fileName = QFileDialog::getSaveFileName(this, tr("选择保存位置"), QApplication::applicationDirPath() + "/", "gif图片(*.gif)");
        if (d_ptr->fileName.isEmpty())
            return;

        clearWriter();
        int width = ui->spinBox_32->value();
        int height = ui->spinBox_33->value();
        d_ptr->fps = ui->spinBox_31->value();

        d_ptr->gifWriter = new Gif::GifWriter;
        if (!d_ptr->gif->GifBegin(d_ptr->gifWriter, d_ptr->fileName.toStdString().c_str(), width, height, d_ptr->fps))
        {
            clearWriter();
            return;
        }
        saveImage();
        d_ptr->timer->start(1000 / d_ptr->fps);
        ui->label_34->setText(tr("开始录制..."));
    }
    d_ptr->isStart = !d_ptr->isStart;
    ui->spinBox_31->setEnabled(!d_ptr->isStart);
    ui->spinBox_32->setEnabled(!d_ptr->isStart);
    ui->spinBox_33->setEnabled(!d_ptr->isStart);
    ui->pushButton_31->setText(d_ptr->isStart ? tr("停 止") : tr("开 始"));
}

void HGifWidget::resizeScreenshot()
{
    int width = ui->spinBox_32->value();
    int height = ui->spinBox_33->value();
    resize(width, height + ui->widget_1->height() + ui->widget_3->height());
}

void HGifWidget::clearWriter()
{
    if (d_ptr->gifWriter == nullptr)
        return;
    delete d_ptr->gifWriter;
    d_ptr->gifWriter = nullptr;
}

void HGifWidget::init()
{
    auto qss = QStringList() << "QLabel { color:#ffffff; } "
                             << "#pushButton_11, #pushButton_12 { border:none; border-radius:0px; }"
                             << "#pushButton_12:hover { background-color:#ff0000; }"
                             << "#pushButton_12{ border-top-right-radius:5px; }"
                             << "#label_11{ font:bold 16px; }"
                             << "#labStatus{ font:15px; }";

    d_ptr->filter = new HMoveEventFilter(this);
    d_ptr->filter->addWatched(this);
    d_ptr->gif = new Gif;
    d_ptr->timer = new QTimer(this);
    d_ptr->timer->setInterval(100);
    ui->spinBox_31->setValue(d_ptr->fps);
    ui->pushButton_11->setIcon(style()->standardIcon(QStyle::SP_ComputerIcon));
    ui->pushButton_12->setIcon(style()->standardIcon(QStyle::SP_TitleBarCloseButton));
    connect(d_ptr->timer, &QTimer::timeout, this, &HGifWidget::saveImage);
    connect(ui->pushButton_12, &QPushButton::clicked, this, &HGifWidget::closeAll);
    connect(ui->pushButton_31, &QPushButton::clicked, this, &HGifWidget::record);
    connect(ui->spinBox_32, &QSpinBox::editingFinished, this, &HGifWidget::resizeScreenshot);
    connect(ui->spinBox_33, &QSpinBox::editingFinished, this, &HGifWidget::resizeScreenshot);
    setAttribute(Qt::WA_TranslucentBackground);
    setAttribute(Qt::WA_DeleteOnClose);
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint | Qt::WindowStaysOnTopHint);
    setWindowIcon(QIcon(":/image/tools/gifWidget.ico"));
    setStyleSheet(qss.join(""));
}

HE_END_NAMESPACE
