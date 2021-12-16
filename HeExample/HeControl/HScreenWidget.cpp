#include "HScreenWidget_p.h"
#include "HScreenObject.h"
#include <QtCore/QDateTime>
#include <QtGui/QContextMenuEvent>
#include <QtGui/QPainter>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QMenu>

HE_BEGIN_NAMESPACE

HScreenWidget::HScreenWidget(QWidget *parent) :
    QWidget(parent),
    d_ptr(new HScreenWidgetPrivate)
{
    init();
}

HScreenWidget::HScreenWidget(HScreenWidgetPrivate &p, QWidget *parent) :
    QWidget(parent),
    d_ptr(&p)
{
    init();
}

HScreenWidget::~HScreenWidget() = default;

void HScreenWidget::contextMenuEvent(QContextMenuEvent *e)
{
    setCursor(Qt::ArrowCursor);
    d_ptr->menu->exec(e->globalPos());
}

void HScreenWidget::mousePressEvent(QMouseEvent *e)
{
    auto pos = e->pos();
    auto status = d_ptr->screen->status();
    if (status == HScreenObject::Select)
    {
        d_ptr->screen->setStart(pos);
    }
    else if (status == HScreenObject::Mov)
    {
        if (!d_ptr->screen->isInArea(pos))
        {
            d_ptr->screen->setStart(pos);
            d_ptr->screen->setStatus(HScreenObject::Select);
        }
        else
        {
            d_ptr->lastPos = pos;
            setCursor(Qt::SizeAllCursor);
        }
    }
}

void HScreenWidget::mouseMoveEvent(QMouseEvent *e)
{
    auto pos = e->pos();
    auto status = d_ptr->screen->status();
    if (status == HScreenObject::Select)
    {
        d_ptr->screen->setEnd(pos);
    }
    else if (status == HScreenObject::Mov)
    {
        d_ptr->screen->move(pos - d_ptr->lastPos);
        d_ptr->lastPos = pos;
    }
    update();
}

void HScreenWidget::mouseReleaseEvent(QMouseEvent *)
{
    auto status = d_ptr->screen->status();
    if (status == HScreenObject::Select)
        d_ptr->screen->setStatus(HScreenObject::Mov);
    else if (status == HScreenObject::Mov)
        setCursor(Qt::ArrowCursor);
}

void HScreenWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    d_ptr->screen->drawScreen(&painter);
}

void HScreenWidget::showEvent(QShowEvent *)
{
    d_ptr->screen->initScreen();
}

void HScreenWidget::saveScreen()
{
    auto fileName = QString("%1/screen_%2.png").arg(QApplication::applicationDirPath(), QDateTime::currentDateTime().toString("yyyy-MM-dd-HH-mm-ss"));
    d_ptr->screen->saveScreen(fileName);
    close();
}

void HScreenWidget::saveFullScreen()
{
    auto fileName = QString("%1/screen_%2.png").arg(QApplication::applicationDirPath(), QDateTime::currentDateTime().toString("yyyy-MM-dd-HH-mm-ss"));
    d_ptr->screen->saveFullScreen(fileName);
    close();
}

void HScreenWidget::saveAsScreen()
{
    QString name = QString("%1.png").arg(QDateTime::currentDateTime().toString("yyyy-MM-dd-HH-mm-ss"));
    QString fileName = QFileDialog::getSaveFileName(this, "保存图片", name, "png Files (*.png)");
    if (!fileName.endsWith(".png"))
        fileName += ".png";
    if (fileName.length() > 4)
    {
        d_ptr->screen->saveScreen(fileName);
        close();
    }
}

void HScreenWidget::saveAsFullScreen()
{
    QString name = QString("%1.png").arg(QDateTime::currentDateTime().toString("yyyy-MM-dd-HH-mm-ss"));
    QString fileName = QFileDialog::getSaveFileName(this, "保存图片", name, "png Files (*.png)");
    if (!fileName.endsWith(".png"))
        fileName += ".png";
    if (fileName.length() > 4)
    {
        d_ptr->screen->saveFullScreen(fileName);
        close();
    }
}

void HScreenWidget::init()
{
    d_ptr->menu = new QMenu(this);
    d_ptr->menu->addAction(tr("保存当前截图"), this, &HScreenWidget::saveScreen);
    d_ptr->menu->addAction(tr("保存全屏截图"), this, &HScreenWidget::saveFullScreen);
    d_ptr->menu->addAction(tr("截图另存为"), this, &HScreenWidget::saveAsScreen);
    d_ptr->menu->addAction(tr("全屏另存为"), this, &HScreenWidget::saveAsFullScreen);
    d_ptr->menu->addAction(tr("退出截图"), this, &HScreenWidget::close);
    d_ptr->screen = new HScreenObject(this);
    showFullScreen();
}

HE_END_NAMESPACE
