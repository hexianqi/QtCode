#include "HReelWidget_p.h"
#include <QtCore/QTimer>
#include <QtGui/QPainter>

HE_BEGIN_NAMESPACE

HReelWidget::HReelWidget(QWidget *parent) :
    QWidget(parent),
    d_ptr(new HReelWidgetPrivate)
{
    d_ptr->timer = new QTimer(this);
    d_ptr->timer->setInterval(40);
    d_ptr->pixmap = QPixmap(":/Resources/image/like1.png");
    setFixedSize(d_ptr->pixmap.rect().size());
    auto font = this->font();
    font.setPixelSize(36);
    setFont(font);
    connect(d_ptr->timer, &QTimer::timeout, this, &HReelWidget::onTimer);
}

HReelWidget::~HReelWidget()
{
}

void HReelWidget::setNumber(uint value)
{
    if (d_ptr->state != NoRun || d_ptr->currentNumber == value)
        return;

    d_ptr->lastNumber = d_ptr->currentNumber;
    d_ptr->currentNumber = value;
    d_ptr->state = d_ptr->lastNumber > d_ptr->currentNumber ? RuningDown : RuningUp;
    d_ptr->lastImageRect = d_ptr->currentImageRect;
    d_ptr->currentImageRect = d_ptr->pixmap.rect();
    d_ptr->currentImageRect.moveTop(d_ptr->state == RuningUp ? d_ptr->pixmap.rect().height() : -d_ptr->pixmap.rect().height());
    d_ptr->timer->start();
}

void HReelWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setFont(this->font());
    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    if (d_ptr->state == NoRun)
    {
        drawUnit(&painter, rect(), d_ptr->currentNumber);
    }
    else
    {
        drawUnit(&painter, d_ptr->lastImageRect, d_ptr->lastNumber);
        drawUnit(&painter, d_ptr->currentImageRect, d_ptr->currentNumber);
    }
}

void HReelWidget::onTimer()
{
    if (d_ptr->state == RuningUp)
    {
        auto top = d_ptr->currentImageRect.top() - d_ptr->rateFactor;
        if(top <= 0)
        {
            d_ptr->timer->stop();
            d_ptr->state = NoRun;
        }
        else
        {
            whenRuningImageRect_Last.moveTop(whenRuningImageRect_Last.top() - rateFactor);
            whenRuningImageRect_Current.moveTop(top);
        }
    }
    else
    {
        auto currentTop = whenRuningImageRect_Current.top() + rateFactor;
        if(currentTop >= 0)
        {
            timer.stop();
            widgetState = state::noRun;
        }
        else
        {
            whenRuningImageRect_Last.moveTop(whenRuningImageRect_Last.top() + rateFactor);
            whenRuningImageRect_Current.moveTop(currentTop);
        }
    }
    update();

}

HE_END_NAMESPACE


#ifndef REELWIDGET_H
#define REELWIDGET_H

#include <QWidget>


class testReelWidget : public QWidget
{
    Q_OBJECT

public:
    testReelWidget(QWidget *parent = nullptr);
    void setValue(int value);

protected:
    QSize sizeHint() const override;

private:
    QList<ReelWidget *> list;
    QTimer timer;
    void onTimer();
};

#endif // REELWIDGET_H

#include "reelwidget.h"
#include <QPainter>
#include <QPaintEvent>
#include <QHBoxLayout>
#include <QQueue>
#include <random>

void ReelWidget::onTimer()
{

}

void ReelWidget::drawAUnit(const QRect & rect, QPainter * painter, uint number)
{
    painter->drawPixmap(rect,bg);
    painter->setPen(Qt::white);
    painter->drawText(rect,Qt::AlignCenter,QString::number(number));
}

testReelWidget::testReelWidget(QWidget *parent)
    :QWidget(parent)
{
    QHBoxLayout * hb = new QHBoxLayout(this);
    hb->setSpacing(0);

    setValue(123456789);
    connect(&timer,&QTimer::timeout,this,&testReelWidget::onTimer);
    timer.start(2000);
}

void testReelWidget::setValue(int value)
{
    QQueue<int> queue;
    while(value != 0)
    {
        queue.push_front(value % 10);
        value /= 10;
    }
    if(queue.size() != list.size())
    {
        auto layout = this->layout();
        for(auto w : list)
        {
            layout->removeWidget(w);
        }
        qDeleteAll(list);
        list.clear();
        for(auto value : queue)
        {
            auto w = new ReelWidget(this);
            layout->addWidget(w);
            list << w;
        }
    }
    for(int i = 0;i < list.size();++i)
    {
        list[i]->setNewNumber(queue.dequeue());
    }
}

QSize testReelWidget::sizeHint() const
{
    return QSize(list.size() * 55,90);
}

void testReelWidget::onTimer()
{
    static std::uniform_int_distribution<int> u(0,9);//均匀分布
    static std::default_random_engine e;//随机数引擎
    for(auto w : list)
    {
        w->setNewNumber(u(e));
    }
}


