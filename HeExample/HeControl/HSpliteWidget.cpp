#include "HSpliteWidget_p.h"
#include <QtCore/QtMath>
#include <QtGui/QMouseEvent>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMenu>
#include <QtWidgets/QActionGroup>
#include <QtWidgets/QGridLayout>

HE_CONTROL_BEGIN_NAMESPACE

HSpliteWidget::HSpliteWidget(QWidget *parent) :
    QWidget(parent),
    d_ptr(new HSpliteWidgetPrivate)
{
    init();
}

HSpliteWidget::HSpliteWidget(HSpliteWidgetPrivate &p, QWidget *parent) :
    QWidget(parent),
    d_ptr(&p)
{
    init();
}

HSpliteWidget::~HSpliteWidget()
{
}

bool HSpliteWidget::eventFilter(QObject *watched, QEvent *event)
{
    auto e = static_cast<QMouseEvent *>(event);
    if (e != nullptr)
    {
        if (e->type() == QEvent::MouseButtonDblClick)
        {
            auto w = qobject_cast<QLabel *>(watched);
            if (!d_ptr->fullScreen)
            {
                d_ptr->fullScreen = true;
                hideAll();
                d_ptr->gridLayout->addWidget(w, 0, 0);
                w->setVisible(true);
            }
            else
                showWidget();
        }
        else if (e->type() == QEvent::MouseButtonPress && e->button() == Qt::RightButton)
            d_ptr->menu->exec(e->globalPos());
    }

    return QWidget::eventFilter(watched, event);
}

void HSpliteWidget::hideAll()
{
    for (auto w : d_ptr->labels)
    {
        d_ptr->gridLayout->removeWidget(w);
        w->setVisible(false);
    }
}

void HSpliteWidget::showAll()
{
    d_ptr->type = "1-16";
    showWidget();
}

void HSpliteWidget::changeType()
{
    auto a = qobject_cast<QAction *>(sender());
    if (a == nullptr)
        return;
    auto t = a->data().toString();
    if (d_ptr->type == t)
        return;
    d_ptr->type = t;
    hideAll();
    showWidget();
}

void HSpliteWidget::showWidget()
{
    d_ptr->fullScreen = false;
    if (d_ptr->type == "1-4")
        showWidget(0, 2);
    else if (d_ptr->type == "5-8")
        showWidget(4, 2);
    else if (d_ptr->type == "9-12")
        showWidget(8, 2);
    else if (d_ptr->type == "13-16")
        showWidget(12, 2);
    else if (d_ptr->type == "1-6")
        showWidget6(0);
    else if (d_ptr->type == "6-11")
        showWidget6(5);
    else if (d_ptr->type == "11-16")
        showWidget6(10);
    else if (d_ptr->type == "1-8")
        showWidget8(0);
    else if (d_ptr->type == "9-16")
        showWidget8(8);
    else if (d_ptr->type == "1-9")
        showWidget(0, 3);
    else if (d_ptr->type == "8-16")
        showWidget(7, 3);
    else if (d_ptr->type == "1-16")
        showWidget(0, 4);
}

void HSpliteWidget::showWidget(int index, int flag)
{
    for (int i = 0; i < flag * flag && i < d_ptr->totalCount - index; i++)
    {
        auto w = d_ptr->labels[index + i];
        d_ptr->gridLayout->addWidget(w, i / flag, i % flag);
        w->setVisible(true);
    }
}

void HSpliteWidget::showWidget6(int index)
{
    d_ptr->gridLayout->addWidget(d_ptr->labels.at(index + 0), 0, 0, 2, 2);
    d_ptr->gridLayout->addWidget(d_ptr->labels.at(index + 1), 0, 2, 1, 1);
    d_ptr->gridLayout->addWidget(d_ptr->labels.at(index + 2), 1, 2, 1, 1);
    d_ptr->gridLayout->addWidget(d_ptr->labels.at(index + 3), 2, 2, 1, 1);
    d_ptr->gridLayout->addWidget(d_ptr->labels.at(index + 4), 2, 1, 1, 1);
    d_ptr->gridLayout->addWidget(d_ptr->labels.at(index + 5), 2, 0, 1, 1);
    for (int i = 0; i < 6; i++)
        d_ptr->labels.at(index + i)->setVisible(true);
}

void HSpliteWidget::showWidget8(int index)
{
    d_ptr->gridLayout->addWidget(d_ptr->labels.at(index + 0), 0, 0, 3, 3);
    d_ptr->gridLayout->addWidget(d_ptr->labels.at(index + 1), 0, 3, 1, 1);
    d_ptr->gridLayout->addWidget(d_ptr->labels.at(index + 2), 1, 3, 1, 1);
    d_ptr->gridLayout->addWidget(d_ptr->labels.at(index + 3), 2, 3, 1, 1);
    d_ptr->gridLayout->addWidget(d_ptr->labels.at(index + 4), 3, 3, 1, 1);
    d_ptr->gridLayout->addWidget(d_ptr->labels.at(index + 5), 3, 2, 1, 1);
    d_ptr->gridLayout->addWidget(d_ptr->labels.at(index + 6), 3, 1, 1, 1);
    d_ptr->gridLayout->addWidget(d_ptr->labels.at(index + 7), 3, 0, 1, 1);
    for (int i = 0; i < 8; i++)
        d_ptr->labels.at(index + i)->setVisible(true);
}

void HSpliteWidget::init()
{
    d_ptr->gridLayout = new QGridLayout(this);
    auto qss = QStringList() << "QFrame { border:2px solid #000000; }"
                             << "QLabel { font:75 25px; color:#F0F0F0; border:2px solid #AAAAAA; background:#000000; }"
                             << "QLabel:focus { border:2px solid #00BB9E; background:#555555; } ";
    setStyleSheet(qss.join("\n"));
    initLabel();
    initMenu();
    showAll();
    setWindowTitle(tr("分割界面"));
}

void HSpliteWidget::initLabel()
{
    qDeleteAll(d_ptr->labels);
    d_ptr->labels.clear();

    for (int i = 0; i < d_ptr->totalCount; i++)
    {
        auto w = new QLabel;
        w->setObjectName(QString("label_%1").arg(i+1));
        w->installEventFilter(this);
        w->setFocusPolicy(Qt::StrongFocus);
        w->setAlignment(Qt::AlignCenter);
        w->setText(tr("通道 %1").arg(i + 1));
        d_ptr->labels << w;
    }
}

void HSpliteWidget::initMenu()
{
    d_ptr->menu = new QMenu(this);
    d_ptr->menu->addAction(tr("显示所有"), this, &HSpliteWidget::showAll);

    auto menu4 = d_ptr->menu->addMenu("切换到4画面");
    menu4->addAction("1-4", this, &HSpliteWidget::changeType)->setData("1-4");
    menu4->addAction("5-8", this, &HSpliteWidget::changeType)->setData("5-8");
    menu4->addAction("9-12", this, &HSpliteWidget::changeType)->setData("9-12");
    menu4->addAction("13-16", this, &HSpliteWidget::changeType)->setData("13-16");

    auto menu6 = d_ptr->menu->addMenu("切换到6画面");
    menu6->addAction("1-6", this, &HSpliteWidget::changeType)->setData("1-6");
    menu6->addAction("6-11", this, &HSpliteWidget::changeType)->setData("6-11");
    menu6->addAction("11-16", this, &HSpliteWidget::changeType)->setData("11-16");

    auto menu8 = d_ptr->menu->addMenu("切换到8画面");
    menu8->addAction("1-8", this, &HSpliteWidget::changeType)->setData("1-8");
    menu8->addAction("9-16", this, &HSpliteWidget::changeType)->setData("9-16");

    auto menu9 = d_ptr->menu->addMenu("切换到9画面");
    menu9->addAction("1-9", this, &HSpliteWidget::changeType)->setData("1-9");
    menu9->addAction("8-16", this, &HSpliteWidget::changeType)->setData("8-16");
}

HE_CONTROL_END_NAMESPACE
