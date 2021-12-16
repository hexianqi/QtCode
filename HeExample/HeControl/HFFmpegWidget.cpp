#include "HFFmpegWidget_p.h"
#include "HFFmpegThread.h"
#include <QtCore/QTimer>
#include <QtGui/QPainter>

HE_BEGIN_NAMESPACE

HFFmpegWidget::HFFmpegWidget(QWidget *parent) :
    QWidget(parent),
    d_ptr(new HFFmpegWidgetPrivate)
{
    init();
}

HFFmpegWidget::HFFmpegWidget(HFFmpegWidgetPrivate &p, QWidget *parent) :
    QWidget(parent),
    d_ptr(&p)
{
    init();
}

HFFmpegWidget::~HFFmpegWidget()
{
    close();
}

void HFFmpegWidget::setUrl(const QString &value)
{
    d_ptr->ffmpeg->setUrl(value);
}

void HFFmpegWidget::open()
{
    clear();
    d_ptr->ffmpeg->play();
    d_ptr->ffmpeg->start();
}

void HFFmpegWidget::pause()
{
    d_ptr->ffmpeg->pause();
}

void HFFmpegWidget::next()
{
    d_ptr->ffmpeg->next();
}

void HFFmpegWidget::close()
{
    if (d_ptr->ffmpeg->isRunning())
        d_ptr->ffmpeg->stop();
    QTimer::singleShot(1, this, SLOT(clear()));
}

void HFFmpegWidget::clear()
{
    d_ptr->image = QImage();
    update();
}

void HFFmpegWidget::paintEvent(QPaintEvent *)
{
    if (d_ptr->image.isNull())
        return;

    QPainter painter(this);
    painter.drawImage(rect(), d_ptr->image);
}

void HFFmpegWidget::updateImage(const QImage &value)
{
    d_ptr->image = value;
    update();
}

void HFFmpegWidget::init()
{
    d_ptr->image = QImage();
    d_ptr->ffmpeg = new HFFmpegThread(this);
    connect(d_ptr->ffmpeg, &HFFmpegThread::receiveImage, this, &HFFmpegWidget::updateImage);
    setAttribute(Qt::WA_DeleteOnClose, true);
}

HE_END_NAMESPACE
